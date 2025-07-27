#include <cgl/tools/backtrace/backtrace.h>

#ifdef USE_BACKTRACE

#include <cpptrace/cpptrace.hpp>

void printTrace()
{
    cpptrace::stacktrace trace = cpptrace::generate_trace();
    trace.print();
}

void faultHandler(int signal)
{
    printTrace();
    exit(1);
}

#else
void printTrace() {}
#endif

CGL::Backtrace& CGL::Backtrace::instance()
{
    static CGL::Backtrace instance;
    return instance;
}

void CGL::Backtrace::init()
{
    static bool ready = false;
    if (ready)
        return;

    instance();

    #ifdef USE_BACKTRACE
    signal(SIGSEGV, faultHandler);
    signal(SIGFPE, faultHandler);
    #endif

    ready = true;
}

void CGL::Backtrace::print()
{
    printTrace();
}

