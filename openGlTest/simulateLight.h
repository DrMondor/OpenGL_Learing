#ifndef  SIMULATELIGHT_H_
#define SIMULATELIGHT_H_


#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

class simulateLight
{
private:
	double r;
public:

	/*const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
	float factor;
	float fov;
	Camera camera;
	float lastX;
	float lastY;
	bool firstMouse;
	//摄像机
	float deltaTime;
	float lastFrame;

	//光照
	glm::vec3 lightPos;

	float vertices[];*/
	simulateLight(); //构造函数
};

#endif // ! SIMULATELIGHT_H_