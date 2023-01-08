//
//  lesson_05_texture.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/8/23.
//

#include "lesson_05_texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int Lesson05::entry(void) {

    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 05", 800, 600);
        
    float vertices[] = {
        // positions         // colors          // texture coordiates
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // left
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // right
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  0.5f, 1.0f  // top
    };
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    
    GLuint VBO, VAO, texture;
    // create
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenTextures(1, &texture);
    // bind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindTexture(GL_TEXTURE_2D, texture);
    // vetex
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    // texture
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    const char* paths[] = {"lesson5_vertex.glsl", "lesson5_frament.glsl"};
    GLuint shaderProgram = shaderProgramFromFile(types, paths, 2);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
