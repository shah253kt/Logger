#ifndef UNIT_TEST

#include "Logger.h"

#include <Arduino.h>

Logger logger(Serial);

#if defined(ESP32)
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
  logger.success("Test");
  logger.warning("Test");
  logger.critical("Test");
}
#else
int freeMemory();

void setup()
{
  Serial.begin(115200);

  logger.postLog = [](Log log)
  {
    Serial.print("Post-log: ");
    Serial.println(log.data());

    Serial.print("Free memory: ");
    Serial.print(freeMemory());
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
  logger.success("Test");
  logger.warning("Test");
  logger.critical("Test");
}

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char *sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif // __arm__

int freeMemory()
{
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char *>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}
#endif

#endif