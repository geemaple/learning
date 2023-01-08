//
//  opengl_glsl_lang.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#include "opengl_glsl_lang.hpp"

void queryVertexShaderInputLimit() {
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

GLuint comipleShader(GLenum shaderType, const GLchar *code) {
    // shader
    GLuint shader = glCreateShader(shaderType);
    
    // compile
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        std::cout << shaderType << std::endl << code << std::endl;
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    return shader;
}

GLuint linkProgramFrom(GLuint shaders[], int count) {
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

GLuint shaderProgramFromFile(GLenum types[], const GLchar* paths[], int count) {
    std::string codes[count];
    
    for (int i = 0; i < count; ++i) {
        std::string source;
        std::stringstream glslStream;
        std::ifstream fileStream;
        fileStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try {
            fileStream.open(paths[i]);
            glslStream << fileStream.rdbuf();
            fileStream.close();
            
            codes[i] = glslStream.str();
        } catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
    }
    
    GLuint shaders[count];
    for (int i = 0; i < count; ++i) {
        shaders[i] = comipleShader(types[i], codes[i].c_str());
    }
    
    return linkProgramFrom(shaders, count);
}

GLuint shaderProgramFromSource(GLenum types[], const GLchar* codes[], int count) {

    GLuint shaders[count];
    for (int i = 0; i < count; ++i) {
        shaders[i] = comipleShader(types[i], codes[i]);
    }

    return linkProgramFrom(shaders, count);
}
