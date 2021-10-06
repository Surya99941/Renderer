#include <iostream>
#include <Window.h>
#include<signal.h>
#define ASSERT(x) if(!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))
using namespace std;

static void GLClearError()
{
    while(glGetError()!=GL_NO_ERROR);
}
static bool GLLogCall(const char* function ,const char* file ,int line)
{
        while(GLenum error = glGetError())
        {
            std::cout<<"[OpenGL Error](" <<error<<")"<<function<<" "<<file<<":"<<line<<std::endl;
            return false;
        }
        return true;
}

float vertices[] = {
     1.0f,  1.0f, 0.0f, //top right
     1.0f,  0.5f, 0.0f, //right
    -1.0f,  1.0f, 0.0f, //top left
    -1.0f,  0.5f, 0.0f  //left
};

unsigned int indices[] = {
    0,1,2, //top right
    2,3,1  //bottom left
};

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\0";


int main()
{
    Window mywindow(1280,720,"Glfw Window");
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    GLCall(glGenBuffers(1,&VBO));
    GLCall(glGenVertexArrays(1,&VAO));
    GLCall(glGenBuffers(1,&EBO));
    GLCall(glBindVertexArray(VAO));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,VBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    unsigned int vertexshader;
    unsigned int fragmentshader;
    unsigned int shaderprogram;

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertexshader,1,&vertexShaderSource,NULL));
    GLCall(glCompileShader(vertexshader));
    int success;
    char infolog[512];
    GLCall(glGetShaderiv(vertexshader,GL_COMPILE_STATUS,&success));
    if(!success){
        GLCall(glGetShaderInfoLog(vertexshader,512,NULL,infolog));
        fprintf(stderr,infolog);
    }

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragmentshader,1,&fragmentShaderSource,NULL));
    GLCall(glCompileShader(fragmentshader));
    GLCall(glGetShaderiv(fragmentshader,GL_COMPILE_STATUS,&success));
    if(!success){
        GLCall(glGetShaderInfoLog(fragmentshader,512,NULL,infolog));
        fprintf(stderr,infolog);
    }

    shaderprogram = glCreateProgram();
    GLCall(glAttachShader(shaderprogram,vertexshader));
    GLCall(glAttachShader(shaderprogram,fragmentshader));
    GLCall(glLinkProgram(shaderprogram));
    GLCall(glGetProgramiv(shaderprogram,GL_LINK_STATUS,&success));
    if(!success){
        GLCall(glGetProgramInfoLog(shaderprogram,512,NULL,infolog));
        fprintf(stderr,infolog);
    }
    GLCall(glUseProgram(shaderprogram));
    GLCall(glDeleteShader(vertexshader));
    GLCall(glDeleteShader(fragmentshader));

    while(mywindow.isopen()){
        mywindow.swapbuffers();
        GLCall(glClearColor(0.8f, 0.8f, 0.9f, 1.0f));
        GLCall(glUseProgram(shaderprogram));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0));
    }
    return 0;
}
