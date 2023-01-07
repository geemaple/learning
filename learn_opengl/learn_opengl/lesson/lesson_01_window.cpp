//
//  lesson_01_window.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/5/23.
//

#include "lesson_01_window.hpp"

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
