//
//  opengl_input.hpp
//  learn_opengl
//
//  Created by Felix Ji on 1/13/23.
//

#ifndef opengl_input_hpp
#define opengl_input_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void processZoomCapture(GLFWwindow* window, float& fov);
void processMouseCapture(GLFWwindow* window, glm::vec3& cameraFront, float &pitch, float &yaw);
void processArrowKeys(GLFWwindow *window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float deltaTime);

#endif /* opengl_input_hpp */
