//
//  opengl_glsl_lang.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#include "opengl_glsl_lang.hpp"

void query_vertex_shader_input_limit() {
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

unsigned int comipleShader(GLenum shaderType, const GLchar *code) {
    // shader
    unsigned int shader = glCreateShader(shaderType);
    
    // compile
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return shader;
}

GLuint createShaderProgram(GLenum types[], const GLchar* codes[], int count) {

    GLuint shaders[count];
    for (int i = 0; i < count; ++i) {
        shaders[i] = comipleShader(types[i], codes[i]);
    }

    // create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    for (int i = 0; i < count; ++i) {
        glAttachShader(shaderProgram, shaders[i]);
    }
    
    glLinkProgram(shaderProgram);
    
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    for (int i = 0; i < count; ++i) {
        glDeleteShader(shaders[i]);
    }
    
    return shaderProgram;
}
