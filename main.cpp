#include <iostream>
#include <Window.h>

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
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    }
    return 0;
}
