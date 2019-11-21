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
public:
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
	float factor;
	float fov;
	Camera camera;
	float lastX;
	float lastY;
	bool firstMouse;
	//…„œÒª˙
	float deltaTime;
	float lastFrame;

	//π‚’’
	glm::vec3 lightPos;

	float vertices[];
	simulateLight() {
	}
	~simulateLight();
};

#endif // ! SIMULATELIGHT_H_