#include <cstdlib>
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW.\n";
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(960, 540, "dawEmu", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create OpenGL window.\n";
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (gladLoadGL((GLADloadfunc)glfwGetProcAddress) == 0) {
		std::cerr << "Failed to load OpenGL functions.\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	}

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.08f, 0.08f, 0.10f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
