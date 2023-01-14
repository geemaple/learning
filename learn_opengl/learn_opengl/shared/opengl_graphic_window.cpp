//
//  opengl_graphic_window.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#include "opengl_graphic_window.hpp"

static MouseCapture positionCapture = {-1, -1, -1, -1};
static ZoomCapture zoomCapture = {0, 0};
static bool captureUpade = false;
static bool zoomUpade = false;

static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    zoomCapture.xOffset = xOffset;
    zoomCapture.yOffset = yOffset;
    zoomUpade = true;
}

static void mouse_capture_callback(GLFWwindow* window, double xpos, double ypos) {
    positionCapture.lastX = positionCapture.x;
    positionCapture.lastY = positionCapture.y;
    positionCapture.x = xpos;
    positionCapture.y = ypos;
    captureUpade = true;
}

MouseCapture processMouseInput(GLFWwindow *window) {
    if (captureUpade && positionCapture.lastX >= 0 && positionCapture.lastY >= 0) {
        captureUpade = false;
        return positionCapture;
    } else {
        return {positionCapture.x, positionCapture.y, positionCapture.x, positionCapture.y};
    }
}

ZoomCapture processZoomInput(GLFWwindow *window) {
    if (zoomUpade) {
        zoomUpade = false;
        return zoomCapture;
    } else {
        return {0, 0};
    }
}

// handle window resize
void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    // For retina displays width and height will end up significantly higher than the original input values
    std::cout << "window:" << window << " width:" << width << " height:" << height << std::endl;
    glViewport(0, 0, width, height);
}

// handle keyboard input
void processKeyInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// create window to draw
GLFWwindow * createGraphicWindow(const char *title, int width, int height, bool enableMouseCapture) {
    
    positionCapture = {-1, -1, -1, -1};
    zoomCapture = {0, 0};
    captureUpade = false;
    zoomUpade = false;
    
    glfwInit();
    // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
#endif
    
    // create window
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    // make the window's context current
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    
    glfwGetFramebufferSize(window, &width, &height);
    // pixels view port will transform (-1 to 1) to (0, 800) and (0, 600)
    glViewport(0, 0, width, height);
    // We register the callback functions after we've created the window and before the render loop is initiated.
    
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    if (enableMouseCapture) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_capture_callback);
        glfwSetScrollCallback(window, scroll_callback); 
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    
    return window;
}
