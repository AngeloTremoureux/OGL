#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/texture.hpp>

int main(void)
{
	GLFWwindow *window;
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Playground", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("playground_steps/step8/StandardShading.vertexshader", "playground_steps/step8/StandardShading.fragmentshader");

	// Vertex data for a cube
	static const GLfloat g_vertex_buffer_data[] = {

		-1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, 0.2f,
		1.0f, -1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		-1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f,

		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f,

		-1.0f, 1.0f, -1.8f,
		-1.0f, -1.0f, 0.2f,
		-1.0f, -1.0f, -1.8f,

		-1.0f, 1.0f, -1.8f,
		-1.0f, 1.0f, 0.2f,
		-1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, 0.2f,

		1.0f, 1.0f, -1.8f,
		1.0f, -1.0f, -1.8f,
		1.0f, -1.0f, 0.2f,

		-1.0f, 1.0f, 0.2f,
		-1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, -1.8f,

		-1.0f, 1.0f, 0.2f,
		1.0f, 1.0f, -1.8f,
		1.0f, 1.0f, 0.2f,

		-1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, -1.8f,

		-1.0f, -1.0f, 0.2f,
		1.0f, -1.0f, -1.8f,
		-1.0f, -1.0f, -1.8f};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Colors for each vertex.
	static const GLfloat g_color_buffer_data[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,

		1.0, 0.0f, 0.0f,
		1.0, 0.0f, 0.0f,
		1.0, 0.0f, 0.0f,

		1.0, 0.0f, 0.0f,
		1.0, 0.0f, 0.0f,
		1.0, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f};
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// Normals for each face (assuming outward-facing normals)
	static const GLfloat g_normal_buffer_data[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f};
	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data),
				 g_normal_buffer_data, GL_STATIC_DRAW);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)	// Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Matrice de translation
	glm::mat4 Translate = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, -3.0f,
									0.0f, 0.0f, 0.0f, 1.0f);
	// Matrice d'Homotetie
	glm::mat4 Scale = glm::mat4(1.20f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.5f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 1.0f);
	// Matrice de Rotation
	glm::mat4 Rotate = glm::mat4(0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 1.0f, 0.f, 0.0f,
								 1.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f);
	Model = Rotate * Scale * Translate * Model;
	glm::mat4 MVP = Projection * View * Model;

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float angle = 0.0f;

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	glm::vec3 lightPos = glm::vec3(4, 4, 1);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	do
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		angle += 3.14159f / 2.0f * deltaTime;
		float c = (float)cos(angle);
		float s = (float)sin(angle);

		Model = {c, 0.0f, s, 0.0f,
				 0.0f, 1.0f, 0.0f, 0.0f,
				 -s, 0.0f, c, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f};
		MVP = Projection * View * Model;
		// Model = glm::translate(Model, glm::vec3(0.0f, 0.001f, 0.0f));
		// Model = glm::scale(Model, glm::vec3(1.001f, 1.001f, 1.0f));
		// Model = glm::rotate(Model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		// Vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,		  // attribute 0.
			3,		  // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void *)0 // array buffer offset
		);

		// Colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1, // attribute 1.
			// No particular reason for 1, but must match the layout in the shader.
			3,		  // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void *)0 // array buffer offset
		);

		// Normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			2,		  // attribute 2.
			3,		  // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0,		  // stride
			(void *)0 // array buffer offset
		);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]));
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}