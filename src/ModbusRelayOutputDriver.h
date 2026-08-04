#pragma once

// Driver wyjść Modbus dla OutputBackend::ModbusRelay32CH.
// Obsługuje jeden moduł domyślny Waveshare. Parametr slaveId zostaje w API,
// żeby później łatwo dodać kilka modułów przekaźnikowych na jednej magistrali.

class ModbusRelayOutputDriver
{
  public:
    ModbusRelayOutputDriver() : _module(nullptr) {}

    void attach(WaveshareRelay32CH& module)
    {
      _module = &module;
    }

    bool isReady() const
    {
      return _module != nullptr && _module->isReady();
    }

    bool write(byte slaveId, byte channel, bool state)
    {
      if (!isReady()) {
        return false;
      }

      // Etap 8: jeden obiekt WaveshareRelay32CH. Jeżeli w konfiguracji pojawi się
      // inny slaveId niż przypisany do tego obiektu, nie wysyłamy polecenia.
      if (slaveId != _module->slaveId()) {
        return false;
      }

      return _module->writeChannel(channel, state);
    }

    bool readAll(uint32_t& stateMask)
    {
      if (!isReady()) {
        stateMask = 0;
        return false;
      }

      return _module->readAll(stateMask);
    }

  private:
    WaveshareRelay32CH* _module;
};

extern ModbusRelayOutputDriver modbusRelayOutput;
