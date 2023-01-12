//
//  lesson_06_transform.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/9/23.
//

#include "lesson_06_transform.hpp"

int Lesson06::entry(void) {

    // create window
    GLFWwindow* window = createGraphicWindow("OpenGL Lesson 06", 800, 600, false);
        
    float vertices[] = {
        // positions         // colors
        -0.433f, -0.25f, 0.0f,  1.0f, 0.0f, 0.0f,  // left
        0.433f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,  // right
        0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // top
    };
    
    GLuint VBO, VAO;
    // create
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // vetex
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLenum types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
    const char* paths[] = {"lesson_06_vertex.glsl", "lesson_06_frament.glsl"};
    GLuint shaderProgram = shaderProgramFromFile(types, paths, 2);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // render loop, each iteration is called a frame
    while(!glfwWindowShouldClose(window))
    {
        processKeyInput(window);
        
        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(2, 2, 2));
        
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        
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
