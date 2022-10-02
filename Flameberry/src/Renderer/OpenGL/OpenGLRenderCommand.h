#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

namespace Flameberry {
    class OpenGLRenderCommand
    {
    public:
        static std::tuple<std::string, std::string> ReadShaderSource(const std::string& filePath);
        static uint32_t CreateTexture(const std::string& filePath);
        static uint32_t CreateShader(const std::string& filePath);
        static glm::vec3 PixelToOpenGL(const glm::vec3& coords, const glm::vec2& viewportSize, float zNear, float zFar);
        static glm::vec2 PixelToOpenGL(const glm::vec2& coords, const glm::vec2& viewportSize);
        static float PixelToOpenGLX(float pixels, const glm::vec2& viewportSize);
        static float PixelToOpenGLY(float pixels, float viewportHeight);
    private:
        static uint32_t GetTextureIdIfAvailable(const char* textureFilePath);
    private:
        // Stores the texture IDs of the already loaded textures to be reused
        static std::unordered_map<std::string, uint32_t> s_TextureIdCache;
    };
}