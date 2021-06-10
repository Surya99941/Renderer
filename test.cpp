#include <shader.h>

int main(){
    Shader file("/home/surya/Documents/programming/opengl/shaders/vertex.glsl");
    std::cout<<file.shader_src<<"Integer?:"<<file.a;

    return 0;
}

