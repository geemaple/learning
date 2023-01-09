//
//  opengl_glsl_lang.hpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#ifndef opengl_glsl_lang_hpp
#define opengl_glsl_lang_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void queryVertexShaderInputLimit();

GLuint shaderProgramFromFile(GLenum types[], const GLchar* paths[], int count);

GLuint shaderProgramFromSource(GLenum types[], const GLchar* codes[], int count);

#endif /* opengl_glsl_lang_hpp */
