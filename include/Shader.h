#ifndef SHADER_H
#define SHADER_H
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Log.h>
#include <errno.h>

class Shader
{
    public:
        Shader(const char* path);
        ~Shader();
        void bind_shader();
        void unbind_shader();

    protected:

    private:
        FILE* shaderfile;
        void m_read();
        void m_count_size();
        void m_compile_shader(unsigned int shaderid,char* source);
        void m_add_program();

        char* vertexsource;
        char* fragmentsource;
        int vertexsize;
        int fragsize;
        Log shaderlog;
        unsigned int m_vertexshader;
        unsigned int m_fragmentshader;
        unsigned int m_shaderprogram;
};

#endif // SHADER_H
