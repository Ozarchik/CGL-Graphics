#pragma once

#include <string>
#include <iostream>

namespace CGL {
struct Texture {
    unsigned int id = -1;
    std::string type = "";
    std::string path = "";
};
}
