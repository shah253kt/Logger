#include "Logger.h"

namespace
{
    constexpr auto MAX_LOG_LENGTH = 15;
}

Logger::Logger(Stream &stream)
    : m_stream(&stream),
      m_printToSerial(true)
{
}

void Logger::printToSerial(bool enabled)
{
    m_printToSerial = enabled;
}

void Logger::setSerial(Stream &stream)
{
    m_stream = &stream;
}

void Logger::info(char *data)
{
    log(Log::Level::Info, data);
}

void Logger::info(const char *data)
{
    auto temp = strdup(data);
    info(temp);
    free(temp);
}

void Logger::success(char *data)
{
    log(Log::Level::Success, data);
}

void Logger::success(const char *data)
{
    auto temp = strdup(data);
    success(temp);
    free(temp);
}

void Logger::warning(char *data)
{
    log(Log::Level::Warning, data);
}

void Logger::warning(const char *data)
{
    auto temp = strdup(data);
    warning(temp);
    free(temp);
}

void Logger::critical(char *data)
{
    log(Log::Level::Critical, data);
}

void Logger::critical(const char *data)
{
    auto temp = strdup(data);
    critical(temp);
    free(temp);
}

void Logger::log(Log::Level level, char *data)
{
    const auto levelStr = [level]
    {
        switch (level)
        {
        case Log::Level::Info:
        {
            return "INFO";
        }
        case Log::Level::Success:
        {
            return "SUCCESS";
        }
        case Log::Level::Warning:
        {
            return "WARNING";
        }
        case Log::Level::Critical:
        {
            return "CRITICAL";
        }
        }

        return "N/A";
    }();

    auto dataToLog = new char[((prependLog == nullptr) ? 0 : strlen(prependLog())) + strlen(levelStr) + strlen(data) + ((appendLog == nullptr) ? 0 : strlen(appendLog())) + 20];

    if (prependLog == nullptr)
    {
        sprintf(dataToLog, "%dms,%s,%s", millis(), levelStr, data);
    }
    else
    {
        sprintf(dataToLog, "%s,%dms,%s,%s", prependLog(), millis(), levelStr, data);
    }

    if (appendLog != nullptr)
    {
        strcat(dataToLog, ",");
        strcat(dataToLog, appendLog());
    }

    strcat(dataToLog, "\n");

    if (m_printToSerial)
    {
        m_stream->print(dataToLog);
    }

    if (postLog)
    {
        postLog({level, dataToLog});
    }

    free(dataToLog);
}
