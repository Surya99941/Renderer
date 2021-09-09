#include "Shader.h"

Shader::Shader(const char* filepath)
:vertexsize(0)
,fragsize(0)
,shaderlog("D:\\programming\\OpenGl\\data\\logs\\shader.log")
{
    shaderfile = fopen(filepath,"r");
    if(shaderfile == NULL){
        shaderlog.Error("Error opening shader file");
        shaderlog.Error(strerror(errno));
    }
    m_count_size();
    vertexsource   = static_cast<char*>(malloc(vertexsize));
    fragmentsource = static_cast<char*>(malloc(fragsize));
    m_read();
    printf("size:%d\n%ssize:%d\n%s",vertexsize,vertexsource,fragsize,fragmentsource);
    m_vertexshader   = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    m_compile_shader(m_vertexshader,vertexsource);
    m_compile_shader(m_fragmentshader,fragmentsource);
    free(vertexsource);
    free(fragmentsource);
}
Shader::~Shader()
{
    fclose(shaderfile);
    glDeleteProgram(m_shaderprogram);
}

void
Shader::m_compile_shader(unsigned int shaderid,char* source){
    glShaderSource(shaderid,1,&source,NULL);
    glCompileShader(shaderid);
    int success;
    char infolog[512];
    glGetShaderiv(shaderid,GL_COMPILE_STATUS,&success);
    if(!success){
        printf("%s\n",source);
        glGetShaderInfoLog(shaderid,512,NULL,infolog);
        fprintf(stderr,infolog);
    }
}
void
Shader::m_add_program(){
    int success;
    char infolog[512];
    m_shaderprogram = glCreateProgram();
    glAttachShader(m_shaderprogram,m_vertexshader);
    glAttachShader(m_shaderprogram,m_fragmentshader);
    glLinkProgram(m_shaderprogram);
    glGetProgramiv(m_shaderprogram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(m_shaderprogram,512,NULL,infolog);
        shaderlog.Error(infolog);
    }
    glDeleteShader(m_vertexshader);
    glDeleteShader(m_fragmentshader);
}

void
Shader::bind_shader(){
    glUseProgram(m_shaderprogram);
}

void
Shader::unbind_shader(){
}

void
Shader::m_read(){
    char letter;
    int shader = 0;
    int index[] = {0,0};
    while((letter = getc(shaderfile))!= EOF){
        if(letter == '$'){
            char line[15];
            fgets(line,15,shaderfile);
            if(!strcmp(line,"vertex\n")){
                shader = 0;
            }
            else if(!strcmp(line,"fragment\n")){
                shader = 1;
            }
        }
        else{
            switch(shader){
                case(0):
                    vertexsource[index[shader]] = letter;
                    index[shader]++;
                    break;
                case(1):
                    fragmentsource[index[shader]] = letter;
                    index[shader]++;
                    break;
                default:
                    printf("Default condition reached\n");
            }
        }
    }
    vertexsource[vertexsize] = '\0';
    fragmentsource[fragsize] = '\0';
}

void
Shader::m_count_size(){
    char ch;
    int current;
    while((ch = getc(shaderfile)) != EOF){
        if(ch == '$'){
            char line[15];
            fgets(line,15,shaderfile);
            if(!strcmp(line,"vertex\n")){
                current = 1;
            }
            else if(!strcmp(line,"fragment\n")){
                current = 2;
            }
        }
        else{
            switch(current){
            case 1:
                vertexsize++;
                break;
            case 2:
                fragsize++;
                break;
            default:
                printf("Default condition reached at counting");
            }
        }
    }
    fseek(shaderfile,0,SEEK_SET);
}
