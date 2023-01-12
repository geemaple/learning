//
//  lesson_05_texture.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#include "lesson_05_texture.hpp"

int Lesson05::entry(void) {

    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 05", 800, 600, false);
        
    float vertices[] = {
        // positions         // colors          // texture coordiates
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // left
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // right
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.5f, 1.0f  // top
    };
    
    GLuint VBO, VAO, texture[2];
    // create
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenTextures(2, texture);
    // bind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // vetex
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    const char* paths[] = {"lesson_05_vertex.glsl", "lesson_05_frament.glsl"};
    GLuint shaderProgram = shaderProgramFromFile(types, paths, 2);
    glUseProgram(shaderProgram);
    
    // set uniforms
    load_texture(texture[0], "wall.jpg", GL_RGB, GL_TEXTURE0);
    load_texture(texture[1], "awesomeface.png", GL_RGBA, GL_TEXTURE1);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // render loop, each iteration is called a frame
    while(!glfwWindowShouldClose(window))
    {
        processKeyInput(window);
        
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
    glDeleteTextures(2, texture);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    
    return 0;
}
