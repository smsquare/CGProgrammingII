// Matrix.cpp
//////////////////////////////////////////////////////////////////////////

#include "Matrix.h"

mat4 Matrix::RotateX(mat4 a_matrix, float a_radians) { 
	float cos1 = cos(a_radians);
	float sin1 = -sin(a_radians);
	float sin2 = sin(a_radians);
	float cos2 = cos(a_radians);
	mat4* rotateMatrix = new mat4(
		1, 0, 0, 0,
		0, cos1, sin1, 0,
		0, sin2, cos2,	0,
		0, 0, 0, 1);
	return *rotateMatrix * a_matrix;
}