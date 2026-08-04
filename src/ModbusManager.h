#pragma once

// Wspólna, nieblokująca warstwa nad aktywną magistralą Modbus RTU.
// W aktualnym firmware realizuje bezpieczny tryb TX-only, który został
// potwierdzony sprzętowo i nie blokuje MySensors/OpenHAB.
class ModbusManager
{
  public:
    ModbusManager()
      : _serial(nullptr), _ready(false), _txFrames(0) {}

    void begin(HardwareSerial& serialPort, unsigned long baudRate)
    {
      _serial = &serialPort;
      _serial->begin(baudRate);
      _ready = true;
    }

    bool isReady() const
    {
      return _ready && _serial != nullptr;
    }

    unsigned long txFrames() const
    {
      return _txFrames;
    }

    bool writeSingleCoilTxOnly(byte slaveId, uint16_t coilAddress, uint16_t value)
    {
      if (!isReady()) {
        return false;
      }

      byte frame[8];
      frame[0] = slaveId;
      frame[1] = 0x05;
      frame[2] = highByte(coilAddress);
      frame[3] = lowByte(coilAddress);
      frame[4] = highByte(value);
      frame[5] = lowByte(value);
      appendCrc(frame, 6);

      _serial->write(frame, sizeof(frame));
      _serial->flush();
      _txFrames++;
      return true;
    }

  private:
    HardwareSerial* _serial;
    bool _ready;
    unsigned long _txFrames;

    static uint16_t crc16(const byte* data, byte length)
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

    static void appendCrc(byte* frame, byte dataLength)
    {
      const uint16_t crc = crc16(frame, dataLength);
      frame[dataLength] = lowByte(crc);
      frame[dataLength + 1] = highByte(crc);
    }
};
