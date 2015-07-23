// SYSTEM.Initialize.cpp
//////////////////////////////////////////////////////////////////////////

#include "SYSTEM.Initialize.h"

namespace INITIALIZE {

	void window_refresh_callback(GLFWwindow* window){
		glfwSwapBuffers(window);
	}

	int WindowFailed() {
		if(glfwInit() == GLFW_FAIL){
			fprintf(stderr, "Failed to initialize GLFW\n");
			return EXIT_WITH_ERROR;
		}

		glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Gets working on mac...
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old open gl...

		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);

		if(window == NULL){
			fprintf(stderr, "Failed to create/open GLFW window.\n");
			glfwTerminate();
			return EXIT_WITH_ERROR;
		}

		//Initialize GLEW.
		glfwMakeContextCurrent(window);

		//Ensure we can capture the escape key being pressed below.
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		//glfwSetWindowFocusCallback(window, windowFocusCallback);
		glfwSetWindowRefreshCallback(window, window_refresh_callback);

		return EXIT_WITH_SUCCESS;
	}

	int GlewFailed() {
		glewExperimental = true; //Has to do with core profile.
		if(glewInit() != GLEW_OK){
			fprintf(stderr, "Failed to initialize GLEW\n");
			return EXIT_WITH_ERROR;
		}

		return EXIT_WITH_SUCCESS;
	}
}