#include "Logger.h"

#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Arduino
{
    unsigned long mockMillisValue = 0;

    unsigned long millis()
    {
        return mockMillisValue;
    }
}

#define millis() Arduino::millis()

class MockStream : public Stream
{
public:
    MOCK_METHOD(size_t, write, (uint8_t), (override));
    MOCK_METHOD(int, available, (), (override));
    MOCK_METHOD(int, read, (), (override));
    MOCK_METHOD(int, peek, (), (override));
    MOCK_METHOD(size_t, print, (const char *), ());
};

TEST(mockMillis, returnsMockValue)
{
    // ARRANGE
    Arduino::mockMillisValue = 12345;

    // ACT
    const auto result = millis();

    // ASSERT
    ASSERT_EQ(result, 12345);
}

TEST(logInfo, properlyFormLog)
{
    // ARRANGE
    Arduino::mockMillisValue = 12345;
    MockStream stream;
    Logger logger(stream);
    logger.printToSerial(false);

    // ACT & ASSERT
    EXPECT_CALL(stream, print("12345ms,INFO,This is a test log\n"));
    // logger.info("This is a test log");
}
