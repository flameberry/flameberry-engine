#include "Application.h"
#include <glad/glad.h>

#include "Core.h"
#include "Renderer/Renderer2D.h"
#include "Timer.h"
#include "ImGui/ImGuiLayer.h"

namespace Flameberry {
    Application* Application::s_Instance;
    Application::Application()
    {
        s_Instance = this;
        m_Window = Window::Create();
        ImGuiLayer::OnAttach();
    }

    void Application::Run()
    {
        float last = 0.0f;
        while (m_Window->IsRunning())
        {
            float now = glfwGetTime();
            float delta = now - last;
            last = now;

            this->OnUpdate(delta);

            ImGuiLayer::Begin();
            this->OnUIRender();
            ImGuiLayer::End();

            m_Window->OnUpdate();
        }
    }

    Application::~Application()
    {
        ImGuiLayer::OnDetach();
        glfwTerminate();
        FL_INFO("Ended Application!");
    }
}