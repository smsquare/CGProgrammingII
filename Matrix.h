// Matrix.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "Application.h"

class Matrix {
	public:
		// TODO: Look up operator overloads
		static mat4 RotateX(mat4 a_matrix, float a_radians);
		static mat4 RotateY(mat4 a_matrix, float a_radians);
		static mat4 RotateZ(mat4 a_matrix, float a_radians);

};