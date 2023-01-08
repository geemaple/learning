//
//  lesson_04_vertex.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#include "lesson_04_vertex.hpp"

// vertex shader
const static char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

// fragment shader
const static char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(ourColor, 1.0);\n"
"}\0";

int Lesson04::entry(void) {
    
    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 04", 800, 600);
    query_vertex_shader_input_limit();
    
    GLuint VAO[2], VBO[2], EBO;
    
    // triangle
    float triangle_vertices[] = {
        // positions         // colors
         0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -1.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    
    // rectangle
    float rectangle_vertices[] = {
        // positions         // colors
        0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,    // top left
        1.0f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,    // top right
        1.0f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // bottom right
        0.0f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f     // bottom left
    };

    GLuint indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        2, 3, 0    // second triangle
    };
    
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);
    
    // triangle
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // rectangle
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle_vertices), rectangle_vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    const GLchar* codes[] = {vertexShaderSource, fragmentShaderSource};
    GLuint shaderProgram = createShaderProgram(types, codes, 2);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // render loop, each iteration is called a frame
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw
        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // clean up all the resources
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return 0;
}
