#pragma once

class LightSensorController
{
public:
  LightSensorController()
      : message(ChildId::OUTDOOR_LIGHT_SENSOR, V_LIGHT_LEVEL)
  {
    for (int &reading : readings)
    {
      reading = 0;
    }
  }

  void update()
  {
    const unsigned long currentMillis = millis();

    if (currentMillis - lastSampleMillis < SAMPLE_INTERVAL_MS)
    {
      return;
    }

    lastSampleMillis = currentMillis;

    total -= readings[readIndex];

    readings[readIndex] =
        analogRead(LIGHT_SENSOR_ANALOG_PIN) / 10;

    total += readings[readIndex];

    readIndex++;

    if (readIndex >= numReadings)
    {
      readIndex = 0;
    }

    const int average = total / numReadings;

    const bool firstReport = !hasReported;

    const bool reportIntervalElapsed =
        currentMillis - lastReportMillis >= REPORT_INTERVAL_MS;

    const int difference =
        average > lastAverage
            ? average - lastAverage
            : lastAverage - average;

    const bool valueChangedEnough =
        difference >= CHANGE_THRESHOLD;

    if (
        firstReport ||
        (reportIntervalElapsed && valueChangedEnough))
    {
      send(message.set(average));

      lastAverage = average;
      lastReportMillis = currentMillis;
      hasReported = true;
    }
  }

private:
  static constexpr unsigned long SAMPLE_INTERVAL_MS = 1000UL;
  static constexpr unsigned long REPORT_INTERVAL_MS = 30000UL;
  static constexpr int CHANGE_THRESHOLD = 2;

  int readings[numReadings] = {};
  int readIndex = 0;
  int total = 0;
  int lastAverage = 0;

  unsigned long lastSampleMillis = 0;
  unsigned long lastReportMillis = 0;

  bool hasReported = false;

  MyMessage message;
};
