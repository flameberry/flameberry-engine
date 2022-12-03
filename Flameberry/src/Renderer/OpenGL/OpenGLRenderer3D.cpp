#include "OpenGLRenderer3D.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLRenderCommand.h"
#include "Core/Core.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>

#include "Renderer/ModelLoader.h"
#include "Core/Timer.h"

#include "ECS/Scene.h"

namespace Flameberry {
    OpenGLRenderer3D::OpenGLRenderer3D()
        : m_CameraUniformBuffer(sizeof(CameraUniformBufferData), FL_UNIFORM_BLOCK_BINDING_CAMERA)
    {
    }

    void OpenGLRenderer3D::UpdateViewportSize()
    {
        int width, height;
        glfwGetFramebufferSize(m_UserGLFWwindow, &width, &height);
        m_ViewportSize = { (float)width, (float)height };
    }

    void OpenGLRenderer3D::Begin(const PerspectiveCamera& camera)
    {
        UpdateViewportSize();
        m_AspectRatio = m_ViewportSize.x / m_ViewportSize.y;

        m_UniformBufferData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();

        /* Set Projection Matrix in GPU memory, for all shader programs to access it */
        m_CameraUniformBuffer.Bind();
        m_CameraUniformBuffer.SetData(glm::value_ptr(m_UniformBufferData.ViewProjectionMatrix), sizeof(glm::mat4), 0);
    }

    void OpenGLRenderer3D::End()
    {
        m_CameraUniformBuffer.Unbind();
    }

    void OpenGLRenderer3D::Init(GLFWwindow* window)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        m_UserGLFWwindow = window;
        UpdateViewportSize();
    }

    void OpenGLRenderer3D::CleanUp()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }

    std::shared_ptr<OpenGLRenderer3D> OpenGLRenderer3D::Create()
    {
        return std::make_shared<OpenGLRenderer3D>();
    }
}
