#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <Log.h>


class Window
{
public:
    Window(int width,int height,char* title);
    ~Window();
    bool isopen();
    void swapbuffers(int interval = 1);

protected:

private:
    Log windowLog;
    GLFWwindow* m_window;

    //code organizers
    void callbacks();

    //statics
    static void s_errorcallback(int error, const char* description)
    {
        Log windowLog("D:\\programming\\OpenGl\\data\\logs\\glfw.log");
        windowLog.Error(description);
    }
    static void s_keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    static void s_framebuffersize(GLFWwindow* window,int width,int height)
    {
        glViewport(0,0,width,height);
    }

};

#endif // WINDOW_H
