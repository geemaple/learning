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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

void query_vertex_shader_input_limit();

GLuint createShaderProgram(GLenum types[], const GLchar* codes[], int count);

#endif /* opengl_glsl_lang_hpp */
