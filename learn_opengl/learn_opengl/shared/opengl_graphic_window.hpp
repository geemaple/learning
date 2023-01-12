//
//  opengl_graphic_window.hpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#ifndef opengl_graphic_window_hpp
#define opengl_graphic_window_hpp

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

struct ZoomCapture {
    double xOffset;
    double yOffset;
};

struct MouseCapture {
    double lastX;
    double lastY;
    double x;
    double y;
};

void processKeyInput(GLFWwindow *window);
ZoomCapture processZoomInput(GLFWwindow *window);
MouseCapture processMouseInput(GLFWwindow *window);

GLFWwindow * createGraphicWindow(const char *title, int width, int height, bool enableMouseCapture);
#endif /* opengl_graphic_window_hpp */
