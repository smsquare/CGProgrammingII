// Cube.h
//////////////////////////////////////////////////////////////////////////


#include "Application.h"
#include "Object.h"
#pragma once

class Cube : public Object {
	public:
		Cube();
		Cube(const char* a_meshPath);
		virtual ~Cube();
	public:
		void BuildCube();
};