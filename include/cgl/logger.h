#ifndef LOGGER_H
#define LOGGER_H

#define CGL_CheckErros() CGL::Logger::checkErrors(__FILE__, __LINE__)

namespace CGL {
class Logger
{
public:
    Logger();

    static void checkErrors(const char* file, int line);
};
}

#endif // LOGGER_H
