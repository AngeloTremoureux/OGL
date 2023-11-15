#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/texture.hpp>

using namespace glm;

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

	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("playground_steps/step3/SimpleVertexShader.vertexshader", "playground_steps/step3/SimpleFragmentShader.fragmentshader");

	// Vertex data for three triangles
	static const GLfloat g_vertex_buffer_data[] = {
		// Ligne 1
		-1.0f, -1.0f, 0.0f, // point 1
		-1.0f, 1.0f, 0.0f,	// point 2
		// Ligne 2
		1.0f, 1.0f, 0.0f,  // point 1
		1.0f, -1.0f, 0.0f, // point 2
		// Ligne 3
		-1.0f, -1.0f, 0.0f, // point 1
		1.0f, -1.0f, 0.0f,	// point 2
		// Ligne 4
		-1.0f, 1.0f, 0.0f, // point 1
		1.0f, 1.0f, 0.0f,  // point 2
		// Ligne 5
		-1.0f, -1.0f, 0.0f, // point 1
		1.0f, 1.0f, 0.0f,	// point 2
		// Ligne 6
		-1.0f, 1.0f, 0.0f, // point 1
		0.0f, 1.5f, 0.0f,  // point 2
		// Ligne 7
		1.0f, 1.0f, 0.0f,  // point 1
		0.0f, 1.5f, 0.0f}; // point 2

	// One color for each vertex.
	static const GLfloat g_color_buffer_data[] = {
		// Couleur Triangle 1
		0.0f, 1.0f, 0.0f, // r g b
		0.0f, 1.0f, 0.0f, // r g b
		0.0f, 1.0f, 0.0f, // r g b
		// Couleur Triangle 2
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		// Couleur Triangle 3
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f};

	GLuint vertexbuffer;
	GLuint colorbuffer;
	do
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

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

		// Draw the triangles
		glDrawArrays(GL_LINES, 0, 14);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Cleanup the buffer
		glDeleteBuffers(1, &vertexbuffer);

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// Close OpenGL window and terminate GLFW
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
	glfwTerminate();

	return 0;
}