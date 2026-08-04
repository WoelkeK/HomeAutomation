#pragma once

// Lekki Modbus RTU Master dla Arduino Mega.
// Obsługuje osobną magistralę Modbus dla Waveshare/SDM630/Deye.
// Uwaga sprzętowa Mega 2560:
// - Serial2 zostaje dla MySensors/OpenHAB.
// - Serial3 używa pinów 14/15, a pin 15 jest u Ciebie DE dla MySensors.
// - Dlatego domyślnie Modbus ustawiony jest na Serial1.

class ModbusMaster
{
  public:
    enum Error : byte
    {
      OK = 0,
      NotReady = 1,
      Timeout = 2,
      CrcError = 3,
      WrongSlave = 4,
      WrongFunction = 5,
      ExceptionResponse = 6,
      BufferTooSmall = 7,
      InvalidArgument = 8
    };

    ModbusMaster()
      : _serial(nullptr),
        _timeoutMs(250),
        _retries(2),
        _dePin(255),
        _useDePin(false),
        _lastError(NotReady),
        _lastExceptionCode(0),
        _txFrames(0),
        _rxFrames(0),
        _timeouts(0),
        _crcErrors(0),
        _errors(0)
    {
    }

    void begin(HardwareSerial& serial, unsigned long baudRate, unsigned long timeoutMs, byte retries)
    {
      begin(serial, baudRate, timeoutMs, retries, 255);
    }

    void begin(HardwareSerial& serial, unsigned long baudRate, unsigned long timeoutMs, byte retries, byte dePin)
    {
      _serial = &serial;
      _timeoutMs = timeoutMs;
      _retries = retries;
      _dePin = dePin;
      _useDePin = dePin != 255;
      _lastError = OK;
      _lastExceptionCode = 0;

      if (_useDePin) {
        pinMode(_dePin, OUTPUT);
        digitalWrite(_dePin, LOW); // odbiór
      }

      _serial->begin(baudRate);
    }

    bool isReady() const
    {
      return _serial != nullptr;
    }

    byte lastError() const { return _lastError; }
    byte lastExceptionCode() const { return _lastExceptionCode; }
    unsigned long txFrames() const { return _txFrames; }
    unsigned long rxFrames() const { return _rxFrames; }
    unsigned long timeouts() const { return _timeouts; }
    unsigned long crcErrors() const { return _crcErrors; }
    unsigned long errors() const { return _errors; }

    const char* lastErrorText() const
    {
      return errorText(_lastError);
    }

    static const char* errorText(byte error)
    {
      switch (error) {
        case OK: return "OK";
        case NotReady: return "NotReady";
        case Timeout: return "Timeout";
        case CrcError: return "CrcError";
        case WrongSlave: return "WrongSlave";
        case WrongFunction: return "WrongFunction";
        case ExceptionResponse: return "ExceptionResponse";
        case BufferTooSmall: return "BufferTooSmall";
        case InvalidArgument: return "InvalidArgument";
        default: return "Unknown";
      }
    }

    bool writeSingleCoil(byte slaveId, uint16_t coilAddress, bool state)
    {
      byte request[8];
      request[0] = slaveId;
      request[1] = 0x05;
      request[2] = highByte(coilAddress);
      request[3] = lowByte(coilAddress);
      request[4] = state ? 0xFF : 0x00;
      request[5] = 0x00;
      appendCrc(request, 6);

      byte response[8];
      byte responseLength = 0;

      for (byte attempt = 0; attempt <= _retries; attempt++) {
        if (!transact(request, sizeof(request), response, sizeof(response), responseLength)) {
          continue;
        }

        if (responseLength != sizeof(request)) {
          setError(BufferTooSmall);
          continue;
        }

        bool same = true;
        for (byte i = 0; i < sizeof(request); i++) {
          if (response[i] != request[i]) {
            same = false;
            break;
          }
        }

        if (!same) {
          setError(WrongFunction);
          return false;
        }

        setError(OK);
        return true;
      }

      return false;
    }

    bool writeMultipleCoils(byte slaveId, uint16_t startAddress, uint16_t quantity, const byte* coilBytes, byte coilByteCount)
    {
      if (quantity < 1 || quantity > 1968) {
        setError(InvalidArgument);
        return false;
      }

      const byte expectedBytes = (quantity + 7) / 8;
      if (coilByteCount < expectedBytes || expectedBytes > 32) {
        setError(InvalidArgument);
        return false;
      }

      byte request[8 + 32];
      request[0] = slaveId;
      request[1] = 0x0F;
      request[2] = highByte(startAddress);
      request[3] = lowByte(startAddress);
      request[4] = highByte(quantity);
      request[5] = lowByte(quantity);
      request[6] = expectedBytes;

      for (byte i = 0; i < expectedBytes; i++) {
        request[7 + i] = coilBytes[i];
      }

      const byte lengthWithoutCrc = 7 + expectedBytes;
      appendCrc(request, lengthWithoutCrc);
      const byte requestLength = lengthWithoutCrc + 2;

      byte response[8];
      byte responseLength = 0;

      for (byte attempt = 0; attempt <= _retries; attempt++) {
        if (!transact(request, requestLength, response, sizeof(response), responseLength)) {
          continue;
        }

        if (!validateHeader(response, responseLength, slaveId, 0x0F)) {
          return false;
        }

        if (responseLength != 8 || response[2] != highByte(startAddress) || response[3] != lowByte(startAddress) || response[4] != highByte(quantity) || response[5] != lowByte(quantity)) {
          setError(WrongFunction);
          return false;
        }

        setError(OK);
        return true;
      }

      return false;
    }

    bool readCoils(byte slaveId, uint16_t startAddress, uint16_t quantity, byte* coilBytes, byte coilBytesCapacity, byte& coilBytesRead)
    {
      coilBytesRead = 0;

      if (quantity < 1 || quantity > 2000) {
        setError(InvalidArgument);
        return false;
      }

      const byte expectedDataBytes = (quantity + 7) / 8;
      if (coilBytesCapacity < expectedDataBytes) {
        setError(BufferTooSmall);
        return false;
      }

      byte request[8];
      request[0] = slaveId;
      request[1] = 0x01;
      request[2] = highByte(startAddress);
      request[3] = lowByte(startAddress);
      request[4] = highByte(quantity);
      request[5] = lowByte(quantity);
      appendCrc(request, 6);

      byte response[64];
      byte responseLength = 0;

      for (byte attempt = 0; attempt <= _retries; attempt++) {
        if (!transact(request, sizeof(request), response, sizeof(response), responseLength)) {
          continue;
        }

        if (!validateHeader(response, responseLength, slaveId, 0x01)) {
          return false;
        }

        if (responseLength < 5 || response[2] != expectedDataBytes) {
          setError(BufferTooSmall);
          return false;
        }

        for (byte i = 0; i < expectedDataBytes; i++) {
          coilBytes[i] = response[3 + i];
        }

        coilBytesRead = expectedDataBytes;
        setError(OK);
        return true;
      }

      return false;
    }

    bool readHoldingRegisters(byte slaveId, uint16_t startAddress, uint16_t quantity, uint16_t* registers, byte registerCapacity, byte& registersRead)
    {
      registersRead = 0;

      if (quantity < 1 || quantity > 20 || registerCapacity < quantity) {
        setError(InvalidArgument);
        return false;
      }

      byte request[8];
      request[0] = slaveId;
      request[1] = 0x03;
      request[2] = highByte(startAddress);
      request[3] = lowByte(startAddress);
      request[4] = highByte(quantity);
      request[5] = lowByte(quantity);
      appendCrc(request, 6);

      byte response[64];
      byte responseLength = 0;
      const byte expectedDataBytes = quantity * 2;

      for (byte attempt = 0; attempt <= _retries; attempt++) {
        if (!transact(request, sizeof(request), response, sizeof(response), responseLength)) {
          continue;
        }

        if (!validateHeader(response, responseLength, slaveId, 0x03)) {
          return false;
        }

        if (responseLength < 5 || response[2] != expectedDataBytes) {
          setError(BufferTooSmall);
          return false;
        }

        for (byte i = 0; i < quantity; i++) {
          registers[i] = word(response[3 + (i * 2)], response[4 + (i * 2)]);
        }

        registersRead = quantity;
        setError(OK);
        return true;
      }

      return false;
    }

  private:
    HardwareSerial* _serial;
    unsigned long _timeoutMs;
    byte _retries;
    byte _dePin;
    bool _useDePin;
    byte _lastError;
    byte _lastExceptionCode;
    unsigned long _txFrames;
    unsigned long _rxFrames;
    unsigned long _timeouts;
    unsigned long _crcErrors;
    unsigned long _errors;

    void setError(byte error)
    {
      _lastError = error;
      if (error == Timeout) {
        _timeouts++;
      } else if (error == CrcError) {
        _crcErrors++;
      }
      if (error != OK) {
        _errors++;
      }
    }

    bool transact(const byte* request, byte requestLength, byte* response, byte responseCapacity, byte& responseLength)
    {
      responseLength = 0;
      _lastExceptionCode = 0;

      if (!isReady()) {
        setError(NotReady);
        return false;
      }

      clearRx();

      setTransmitMode();
      _serial->write(request, requestLength);
      _serial->flush();
      setReceiveMode();
      _txFrames++;

      const unsigned long start = millis();
      while (millis() - start < _timeoutMs) {
        while (_serial->available()) {
          if (responseLength >= responseCapacity) {
            setError(BufferTooSmall);
            return false;
          }
          response[responseLength++] = _serial->read();
        }

        if (responseLength >= 5 && isFrameComplete(response, responseLength)) {
          if (!hasValidCrc(response, responseLength)) {
            setError(CrcError);
            return false;
          }
          _rxFrames++;
          return true;
        }
      }

      setError(Timeout);
      return false;
    }

    bool validateHeader(const byte* response, byte responseLength, byte expectedSlave, byte expectedFunction)
    {
      if (responseLength < 5) {
        setError(BufferTooSmall);
        return false;
      }

      if (response[0] != expectedSlave) {
        setError(WrongSlave);
        return false;
      }

      if (response[1] == (expectedFunction | 0x80)) {
        _lastExceptionCode = response[2];
        setError(ExceptionResponse);
        return false;
      }

      if (response[1] != expectedFunction) {
        setError(WrongFunction);
        return false;
      }

      return true;
    }

    bool isFrameComplete(const byte* frame, byte length)
    {
      if (length < 5) {
        return false;
      }

      const byte functionCode = frame[1];

      if (functionCode & 0x80) {
        return length >= 5;
      }

      if (functionCode == 0x01 || functionCode == 0x03) {
        const byte byteCount = frame[2];
        return length >= (byte)(byteCount + 5);
      }

      if (functionCode == 0x05 || functionCode == 0x06 || functionCode == 0x0F) {
        return length >= 8;
      }

      return length >= 5;
    }

    void setTransmitMode()
    {
      if (_useDePin) {
        digitalWrite(_dePin, HIGH);
        delayMicroseconds(50);
      }
    }

    void setReceiveMode()
    {
      if (_useDePin) {
        delayMicroseconds(50);
        digitalWrite(_dePin, LOW);
      }
    }

    void clearRx()
    {
      while (_serial->available()) {
        _serial->read();
      }
    }

    void appendCrc(byte* frame, byte lengthWithoutCrc)
    {
      const uint16_t crc = crc16(frame, lengthWithoutCrc);
      frame[lengthWithoutCrc] = lowByte(crc);
      frame[lengthWithoutCrc + 1] = highByte(crc);
    }

    bool hasValidCrc(const byte* frame, byte length)
    {
      if (length < 3) {
        return false;
      }

      const uint16_t received = word(frame[length - 1], frame[length - 2]);
      const uint16_t calculated = crc16(frame, length - 2);
      return received == calculated;
    }

    uint16_t crc16(const byte* data, byte length)
    {
      uint16_t crc = 0xFFFF;

      for (byte i = 0; i < length; i++) {
        crc ^= data[i];

        for (byte bit = 0; bit < 8; bit++) {
          if (crc & 0x0001) {
            crc >>= 1;
            crc ^= 0xA001;
          } else {
            crc >>= 1;
          }
        }
      }

      return crc;
    }
};
