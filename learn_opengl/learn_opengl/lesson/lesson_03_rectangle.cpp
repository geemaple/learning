//
//  lesson_03_rectangle.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/7/23.
//

#include "lesson_03_rectangle.hpp"
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
"uniform vec4 polygonColor;\n"
"void main()\n"
"{\n"
"    FragColor = polygonColor;\n"
"}\0";

int Lesson03::entry(void) {
    
    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 03", 800, 600);
    queryVertexShaderInputLimit();
    
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    GLuint indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    
    GLuint VAO, VBO, EBO;
    // create
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // bind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    // set
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // agttributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    const GLchar* codes[] = {vertexShaderSource, fragmentShaderSource};
    GLuint shaderProgram = shaderProgramFromSource(types, codes, 2);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // render loop, each iteration is called a frame
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // find variable
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int polygonColor = glGetUniformLocation(shaderProgram, "polygonColor");
        
        // update color
        glUseProgram(shaderProgram);
        glUniform4f(polygonColor, 0.0f, greenValue, 0.0f, 1.0f);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean up all the resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return 0;
}
