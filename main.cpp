#include <iostream>
#include <Window.h>
#include <Shader.h>
#include <signal.h>


#define ASSERT(x) if(!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x,__FILE__,__LINE__))

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
     0.5f,  0.5f, 0.0f, //top right
     0.5f, -0.5f, 0.0f, //bottom right
    -0.5f,  0.5f, 0.0f, //top left
    -0.5f, -0.5f, 0.0f  //bottom left
};

unsigned int indices[] = {
    0,1,2, //top right
    2,3,1  //bottom left
};

int main()
{
    Window mywindow(1280,720,"Glfw Window");
    Shader basic("./data/Shader/simple.glsl");
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
    basic.bind_shader();


    while(mywindow.isopen()){
        mywindow.swapbuffers();
        GLCall(glClearColor(0.8f, 0.8f, 0.9f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0));
    }
    return 0;
}
