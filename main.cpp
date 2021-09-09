#include <iostream>
#include <Window.h>
#include <Shader.h>

using namespace std;

static void GLClearError(){
    while(!glGetError());
}

static void GlCheckError(){
    while(GLenum error = glGetError()){
        printf("OpenGl error code:%d\n",error);
    }
}

float vertices[] = {
     1.0f,  1.0f, 0.0f, //top right
     1.0f,  0.0f, 0.0f, //right
    -1.0f,  1.0f, 0.0f, //top left
    -1.0f,  0.5f, 0.0f  //left
};

unsigned int indices[] = {
    0,1,2, //top right
    2,3,1  //bottom left
};

int main()
{
    Window mywindow(1280,720,"Glfw Window");
    Shader basic_shader("D:/programming/OpenGl/data/Shader/simple.glsl");
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    GlCheckError();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    basic_shader.bind_shader();
    while(mywindow.isopen()){
        mywindow.swapbuffers();
        glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    }
    return 0;
}
