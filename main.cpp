#include <iostream>
#include <Window.h>

using namespace std;


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
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
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vertexshader;
    unsigned int fragmentshader;
    unsigned int shaderprogram;

    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexshader);
    int success;
    char infolog[512];
    glGetShaderiv(vertexshader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertexshader,512,NULL,infolog);
        fprintf(stderr,infolog);
    }

    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentshader);
    glGetShaderiv(fragmentshader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragmentshader,512,NULL,infolog);
        fprintf(stderr,infolog);
    }

    shaderprogram = glCreateProgram();
    glAttachShader(shaderprogram,vertexshader);
    glAttachShader(shaderprogram,fragmentshader);
    glLinkProgram(shaderprogram);
    glGetProgramiv(shaderprogram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderprogram,512,NULL,infolog);
        fprintf(stderr,infolog);
    }
    glUseProgram(shaderprogram);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    while(mywindow.isopen()){
        mywindow.swapbuffers();
        glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
        glUseProgram(shaderprogram);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3);
    }
    return 0;
}
