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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HRIGHT = 720;
float factor = 0.2f;
float fov = 45.0f;

//�����
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HRIGHT / 2;
bool firstMouse = true;

//�����
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//����
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

float vertices[] = {
-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,

-0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,

0.5f, 0.5f, 0.5f,
0.5f, 0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,

-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, 0.5f,
0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, 0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
0.5f, 0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, -0.5f
};
simulateLight::simulateLight()
{

	//main��ʼ
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HRIGHT, "simulateLight Test",NULL,NULL);
	if (window == NULL)
	{
		std:; cout << "Failed to create GLFW window" << std::endl;
		printf("There is something wrong\n");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window,mouse_callback );
	glfwSetScrollCallback(window, scroll_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glEnable(GL_DEPTH_TEST);

	//������ɫ��
	Shader lightingShader("simulateLight/Shader.vs", "simulateLight/Shader.fs");
	Shader lampShader("simulateLight/Shader.vs", "simulateLight/LampShader.fs");
	
	//�������Ի���
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//ѭ��
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.use();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		//ͶӰ
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HRIGHT, 0.1f, 100.0f);
		lightingShader.setMat4("projection", glm::value_ptr(projection));

		//�۲�
		glm::mat4 view;
		view = camera.GetViewMartix();
		lightingShader.setMat4("view", glm::value_ptr(view));

		//model one
		glm::mat4 model1;
		lightingShader.setMat4("model1", glm::value_ptr(model1));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//model two
		lampShader.use();
		lampShader.setMat4("projection", glm::value_ptr(projection));
		lampShader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model2;
		model2 = glm::translate(model2, lightPos);
		model2 = glm::scale(model2, glm::vec3(0.2f));
		lampShader.setMat4("model", glm::value_ptr(model2));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = lastX - xPos;	//�����ˣ��ڴ����У���ߵ�����С���ұߵ����꣬��������Ҫһ�����ĽǶ�
	float yoffset = lastY - yPos;	//ͬ�����ڴ����У���������������������꣬����������̧ͷ��ʱ����Ҫһ�����ĽǶ�
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}