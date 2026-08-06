#pragma once

class LightSensorController
{
  public:
    void update()
    {
      const unsigned long currentMillis = millis();

      if (currentMillis - lastSampleMillis < SAMPLE_INTERVAL_MS) {
        return;
      }

      lastSampleMillis = currentMillis;

      total -= readings[readIndex];

      readings[readIndex] =
          analogRead(LIGHT_SENSOR_ANALOG_PIN) / 10;

      total += readings[readIndex];
      readIndex++;

      if (readIndex >= numReadings) {
        readIndex = 0;
      }

      average = total / numReadings;

      const bool firstReport = !hasReported;
      const bool reportIntervalElapsed =
          currentMillis - lastReportMillis >= REPORT_INTERVAL_MS;

      const int difference =
          average > lastaverage
              ? average - lastaverage
              : lastaverage - average;

      const bool valueChangedEnough =
          difference >= CHANGE_THRESHOLD;

      if (firstReport ||
          (reportIntervalElapsed && valueChangedEnough)) {
        send(msg.set(average));

        lastaverage = average;
        lastReportMillis = currentMillis;
        hasReported = true;
      }
    }

  private:
    static constexpr unsigned long SAMPLE_INTERVAL_MS = 1000UL;
    static constexpr unsigned long REPORT_INTERVAL_MS = 30000UL;
    static constexpr int CHANGE_THRESHOLD = 2;

    unsigned long lastSampleMillis = 0;
    unsigned long lastReportMillis = 0;
    bool hasReported = false;
};
