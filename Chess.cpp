#include "Chess.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Windows.h>

#include "Renderer.h"

void chess::run_graphics(chess::GameManager& new_game) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Retro Shooter", glfwGetPrimaryMonitor(), NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "error!" << std::endl;

	//std::cout << glGetString(GL_VERSION) << std::endl;
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		OpenGL::Renderer renderer;

		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			new_game.render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

	}
	glfwTerminate();
}
void chess::run_game(chess::GameManager& new_game) {
	new_game.start();
}
