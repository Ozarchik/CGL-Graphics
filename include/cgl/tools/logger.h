#ifndef CGL_LOGGER_H
#define CGL_LOGGER_H

#include <iostream>
#include <mutex>

void checkErrors(const char* file, int line);

#define CGL_DEBUG_MESSAGE
#ifdef CGL_DEBUG_MESSAGE
#define cglErrorsCheck() checkErrors(__FILE__, __LINE__)
#else
#define cglErrorsCheck()
#endif


namespace cgl {

enum class LogLevel {
    Debug,
    Info,
    Error,
    Warning
};

class Logger
{
public:
    Logger(LogLevel level)
        : m_level(level)
    {
    }

    template <typename T>
    Logger& operator<<(const T& message)
    {
        std::unique_lock<std::mutex> l(m_mutex);
        static int count = 0;
        std::cout << ++count << ": [" << logLevelString() << "] " << message << std::endl;
        return *this;
    }

    std::string logLevelString() {
        std::string str;
        switch (m_level) {
            case LogLevel::Debug: {
                str = "Debug";
            } break;
            case LogLevel::Error: {
                str = "Error";
            } break;
            case LogLevel::Info: {
                str = "Info";
            } break;
            case LogLevel::Warning: {
                str = "Warning";
            } break;
            default: {
                str = "LogLevel not found";
            }
        }

        return str;
    }

private:
    LogLevel m_level;
    std::mutex m_mutex;
};

Logger cglInfo();
Logger cglDebug();
Logger cglError();
Logger cglWarning();
}

#endif // CGL_LOGGER_H
