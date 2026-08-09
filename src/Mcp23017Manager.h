#pragma once

extern Adafruit_MCP23017 mcp1;
extern Adafruit_MCP23017 mcp2;
extern Adafruit_MCP23017 mcp3;

class Mcp23017Manager
{
  public:
    void begin()
    {
      mcp1.begin(addr1);
      mcp2.begin(addr2);
      mcp3.begin(addr3);
    }

    Adafruit_MCP23017& device(InputDevice inputDevice)
    {
      switch (inputDevice) {
        case InputDevice::MCP1:
          return mcp1;
        case InputDevice::MCP2:
          return mcp2;
        case InputDevice::MCP3:
        default:
          return mcp3;
      }
    }

    void configureInput(InputDevice inputDevice, int pin)
    {
      Adafruit_MCP23017& expander = device(inputDevice);
      expander.pinMode(pin, INPUT);
      expander.pullUp(pin, HIGH);
    }
};
