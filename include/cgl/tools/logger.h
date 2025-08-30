#ifndef CGL_LOGGER_H
#define CGL_LOGGER_H

#include <iostream>

void checkErrors(const char* file, int line);

#define CGL_DEBUG_MESSAGE
#ifdef CGL_DEBUG_MESSAGE
#define cglErrors() checkErrors(__FILE__, __LINE__)
#else
#define cglErrorsCheck()
#endif


namespace cgl {
class Logger
{
public:
    Logger() = default;
};
}

#endif // CGL_LOGGER_H
