#pragma once

class Log
{
public:
    enum class Level
    {
        Info,
        Success,
        Warning,
        Critical
    };

    Log(Level level, const char *data);
    Log(Level level, char *data);
    Log(const Log &other);
    ~Log();

    Log &operator=(const Log &other);
    [[nodiscard]] bool operator==(const Log &other) const;

    [[nodiscard]] Level level() const;
    [[nodiscard]] char *data() const;

private:
    Level m_level;
    char *m_data;
};
