#ifndef UNIT_TEST

#include "Logger.h"

#include <Arduino.h>

Logger logger(Serial);

void setup()
{
  Serial.begin(115200);

  logger.postLog = [](Log log)
  {
    Serial.printf("Post-log: %s\n", log.data());

    size_t freeHeap = ESP.getFreeHeap();
    Serial.print("Free heap memory: ");
    Serial.print(freeHeap);
    Serial.println(" bytes");

    size_t maxAllocHeap = ESP.getMaxAllocHeap();
    Serial.print("Maximum allocatable heap: ");
    Serial.print(maxAllocHeap);
    Serial.println(" bytes");

    size_t minFreeHeap = ESP.getMinFreeHeap();
    Serial.print("Minimum free heap since start: ");
    Serial.print(minFreeHeap);
    Serial.println(" bytes");
  };

  logger.prependLog = []
  {
    return "MyLog";
  };

  logger.appendLog = []
  {
    return "Done";
  };
}

void loop()
{
  logger.info("Test");
}

#endif