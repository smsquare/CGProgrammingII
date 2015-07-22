// Cube.h
//////////////////////////////////////////////////////////////////////////


#include "Application.h"
#include "Object.h"
#pragma once

class Cube : public Object {
	public:
		Cube();
		virtual ~Cube();
	public:
		void BuildCube();
};