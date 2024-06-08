#include "Logger.h"

Logger logger(Serial);

void setup()
{
    Serial.begin(115200);

    // If you want to log the data in an SD card, this is a place you could do so.
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

    // You can inject RTC timestamp here, for example.
    logger.prependLog = []
    {
        return "MyLog";
    };

    // You can additional data at the end of the log.
    logger.appendLog = []
    {
        return "Done";
    };
}

void loop()
{
    logger.info("Test");
    // logger.success("Test");
    // logger.warning("Test");
    // logger.critical("Test");
}