#pragma once

#include "Application.h"

namespace USERINPUT {
	enum Key { 
		// WASD:
		W=GLFW_KEY_W, A=GLFW_KEY_A, S=GLFW_KEY_S, D=GLFW_KEY_D,
		// ARROW KEYS: Up, Down, Left, Right
		UP=GLFW_KEY_UP, DOWN=GLFW_KEY_DOWN, LEFT=GLFW_KEY_LEFT, RIGHT=GLFW_KEY_RIGHT
	};

	bool IsKeyPressed(Key a_key);
}