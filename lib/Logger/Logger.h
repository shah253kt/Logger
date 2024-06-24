#pragma once

#include "Log.h"

#include <Arduino.h>

#define DEFAULT_STREAM Serial

class Logger
{
public:
    Logger(Stream &stream = DEFAULT_STREAM);
    ~Logger() = default;

    void printToSerial(bool enabled);
    void setSerial(Stream &stream);

    void info(char *data);
    void info(const char *data);

    void success(char *data);
    void success(const char *data);

    void warning(char *data);
    void warning(const char *data);

    void critical(char *data);
    void critical(const char *data);

    const char *(*prependLog)();
    const char *(*appendLog)();
    void (*postLog)(Log log);

private:
    Stream *m_stream;
    bool m_printToSerial;

    void log(Log::Level level, char *data);
};
