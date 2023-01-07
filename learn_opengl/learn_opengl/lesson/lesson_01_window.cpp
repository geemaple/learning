//
//  lesson_01_window.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/5/23.
//

#include "lesson_01_window.hpp"

// handle window resize
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // For retina displays width and height will end up significantly higher than the original input values
    std::cout << "window:" << window << " width:" << width << " height:" << height << std::endl;
    glViewport(0, 0, width, height);
}

// handle keyboard input
static void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// create window to draw
static GLFWwindow * createGraphicWindow(const char *title, int width, int height) {
    glfwInit();
    // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // core mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
    
    // pixels view port will transform (-1 to 1) to (0, 800) and (0, 600)
    glViewport(0, 0, width, height);
    // We register the callback functions after we've created the window and before the render loop is initiated.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    return window;
}

int Lesson01::entry(void) {
    
    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 01", 800, 600);
    
    // render loop, each iteration is called a frame
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean up all the resources
    glfwTerminate();
    return 0;
}
