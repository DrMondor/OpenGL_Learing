#include "simulateLight.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "makeWindow.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

using namespace std;
simulateLight::simulateLight()
{
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HRIGHT = 720;
	float factor = 0.2f;
	float fov = 45.0f;

	//ÉãÏñ»ú
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2;

	
	printf("dasda");
}

