#include "Log.h"

#include "Arduino.h"

Log::Log(Level level, const char *data) : m_level(level), m_data(strdup(data))
{
}

Log::Log(Level level, char *data) : m_level(level)
{
    if (data)
    {
        m_data = new char[strlen(data) + 1];
        strcpy(m_data, data);
    }
}

Log::Log(const Log &other) : m_level(other.level())
{
    if (other.data())
    {
        m_data = new char[strlen(other.data()) + 1];
        strcpy(m_data, other.data());
    }
}

Log::~Log()
{
    delete[] m_data;
}

Log &Log::operator=(const Log &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] m_data;

    m_level = other.level();
    if (other.data())
    {
        m_data = new char[strlen(other.data()) + 1];
        strcpy(m_data, other.data());
    }
    else
    {
        m_data = nullptr;
    }

    return *this;
}

bool Log::operator==(const Log &other) const
{
    if (m_level != other.level())
    {
        return false;
    }

    if (m_data == nullptr && other.data() == nullptr)
    {
        return true;
    }

    if (m_data == nullptr || other.data() == nullptr)
    {
        return false;
    }

    return strcmp(m_data, other.data()) == 0;
};

Log::Level Log::level() const
{
    return m_level;
}

char *Log::data() const
{
    return m_data;
}
