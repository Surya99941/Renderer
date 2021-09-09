#include "Window.h"

Window::Window(int width,int height,char* title)
    :windowLog("D:\\programming\\OpenGl\\data\\logs\\window.log")
{
    glfwSetErrorCallback(s_errorcallback);
    if(glfwInit())
    {
        windowLog.Info("Initialized Glfw success");
    }
    else
    {
        windowLog.Error("Initialized Glfw failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    m_window = glfwCreateWindow(width,height,title,NULL,NULL);
    if(!m_window)
    {
        windowLog.Error("Window creation failed\n");
    }
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    callbacks();
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void
Window::callbacks()
{
    glfwSetKeyCallback(m_window,s_keycallback);
    glfwSetFramebufferSizeCallback(m_window,s_framebuffersize);
}

bool
Window::isopen()
{
    return !glfwWindowShouldClose(m_window);
}

void
Window::swapbuffers(int interval)
{
    glfwSwapBuffers(m_window);
    glfwSwapInterval(interval);
    glfwPollEvents();
}
