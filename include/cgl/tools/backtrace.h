#ifndef CGL_BACKTRACE_H
#define CGL_BACKTRACE_H

namespace cgl {
class Backtrace {
    Backtrace() = default;

public:
    static Backtrace& instance();
    static void init();
    static void print();


};
}

#endif