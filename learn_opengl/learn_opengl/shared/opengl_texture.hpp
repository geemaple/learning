//
//  opengl_texture.hpp
//  learn_opengl
//
//  Created by Felix Ji on 1/10/23.
//

#ifndef opengl_texture_hpp
#define opengl_texture_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

void load_texture(GLuint texture, const char *path, GLenum format, GLenum index);

#endif /* opengl_texture_hpp */
