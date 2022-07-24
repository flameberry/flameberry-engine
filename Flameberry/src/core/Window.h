#pragma once
#include <memory>
#include <GLFW/glfw3.h>

namespace Flameberry {
    class Window
    {
    public:
        static std::shared_ptr<Window> Create(int width = 1280, int height = 720, const char* title = "Flameberry Engine");

        Window(int width = 1280, int height = 720, const char* title = "Flameberry Engine");
        ~Window();

        bool IsRunning();
        void OnUpdate();
    private:
        GLFWwindow* M_Window;
        int M_Width, M_Height;
        const char* M_Title;
    };
}