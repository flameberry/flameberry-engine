#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

#include "OpenGLVertex.h"

namespace Flameberry {
    struct ModelData {
        std::vector<OpenGLVertex2D> Vertices;
        std::vector<uint32_t> Indices;
    };

    class OpenGLRenderCommand
    {
    public:
        static std::tuple<std::string, std::string> ReadShaderSource(const std::string& filePath);
        static uint32_t CreateTexture(const std::string& filePath);
        static uint32_t CreateShader(const std::string& filePath);
        static std::tuple<std::vector<OpenGLVertex>, std::vector<uint32_t>> LoadModel(const std::string& filePath);
        static ModelData LoadModelData(const std::string& filePath);
    private:
        static uint32_t GetTextureIdIfAvailable(const char* textureFilePath);
    private:
        // Stores the texture IDs of the already loaded textures to be reused
        static std::unordered_map<std::string, uint32_t> s_TextureIdCache;
    };
}
