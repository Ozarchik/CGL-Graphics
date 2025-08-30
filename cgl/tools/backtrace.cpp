#include <cgl/tools/backtrace.h>

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

cgl::Backtrace& cgl::Backtrace::instance()
{
    static cgl::Backtrace instance;
    return instance;
}

void cgl::Backtrace::init()
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

void cgl::Backtrace::print()
{
    printTrace();
}

