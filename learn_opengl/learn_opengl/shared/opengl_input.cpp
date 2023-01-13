//
//  opengl_input.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/13/23.
//

#include "opengl_input.hpp"
#include "opengl_graphic_window.hpp"

void processZoomCapture(GLFWwindow* window, float& fov) {
    ZoomCapture zoom = processZoomInput(window);
    fov -= (float)zoom.yOffset;
    
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void processMouseCapture(GLFWwindow* window, glm::vec3& cameraFront, float &pitch, float &yaw) {
    MouseCapture capture = processMouseInput(window);
    
    float xoffset = capture.x - capture.lastX;
    float yoffset = capture.lastY - capture.y; // reversed since y-coordinates range from bottom to top
    
    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void processArrowKeys(GLFWwindow *window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float deltaTime)
{
    processKeyInput(window);
    
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += glm::normalize(cameraFront) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= glm::normalize(cameraFront) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS or glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
