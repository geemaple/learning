//
//  lesson_02_triangle.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/6/23.
//

#include "lesson_02_triangle.hpp"

// vertex shader
const static char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// fragment shader
const static char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int Lesson02::entry(void) {

    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 02", 800, 600);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, //left
        0.5f, -0.5f, 0.0f, //right
        0.0f,  0.5f, 0.0f  // top
    };
    
    GLuint VBO, VAO;
    // create VBO
    glGenBuffers(1, &VBO);
    // bind
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // copy data to the bond buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // agttributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    const GLchar* codes[] = {vertexShaderSource, fragmentShaderSource};
    GLuint shaderProgram = shaderProgramFromSource(types, codes, 2);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop, each iteration is called a frame
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean up all the resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return 0;
}
