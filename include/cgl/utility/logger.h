#ifndef CGL_LOGGER_H
#define CGL_LOGGER_H

void checkErrors(const char* file, int line);

#define CGL_DEBUG_MESSAGE
#ifdef CGL_DEBUG_MESSAGE
#define CGL_CheckErros() checkErrors(__FILE__, __LINE__)
#else
#define CGL_CheckErros()
#endif


namespace CGL {
class Logger
{
public:
    Logger() = default;
};
}

#endif // CGL_LOGGER_H
