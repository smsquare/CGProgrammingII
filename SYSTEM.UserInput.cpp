#include "SYSTEM.UserInput.h"

namespace USERINPUT {
	//enum Key { A=GLFW_KEY_A, D=GLFW_KEY_D};
	bool IsKeyPressed(USERINPUT::Key a_key) {
		return (glfwGetKey(window, a_key) == GLFW_PRESS) ? true : false;
	}
}