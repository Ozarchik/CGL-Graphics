#pragma once

#include <string>
#include <iostream>

namespace CGL {
struct TextureBase {
    unsigned int id;
    std::string type;
    std::string path;
};
}
