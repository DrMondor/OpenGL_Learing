#ifndef makeWindow_H_
#define makeWindow_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void processInput(GLFWwindow *window, float deltaTime, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
#endif);