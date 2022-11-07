#pragma once

#include <string>
#include <tuple>

#include "OpenGL/OpenGLVertex.h"

namespace Flameberry {
    class ModelLoader
    {
    public:
        static std::tuple<std::vector<OpenGLVertex>, std::vector<uint32_t>> LoadOBJ(const std::string& modelPath);
        static float ParseFloat(const char* str, char delimiter = ' ');
    private:
    };
}
