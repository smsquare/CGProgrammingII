#include "Application.h"

#pragma once

class Object{

	public:
		Object();

		virtual ~Object();
		virtual void Update(const float& a_deltaTime);
		virtual void Render(const Camera& a_camera);

		void SetPosition(vec3 a_position);
		void SetRotation(vec3 a_rotation);
		void SetRotationSpeed(float a_rotSpeed);
		void SetScale(vec3 a_scale);


		vec3 GetPosition();
		float GetLeftX();
		float GetRightX();
		float GetTopY();
		float GetBottomY();

		void SaveObjectState(char *a_message = "Saved Object State");
		void LoadObjectState(char *a_message = "Loaded Object State");
		GLuint LoadBMP(const char * a_imagepath);

	protected:
		void BuildTriangles(const GLuint& a_perRow, const GLuint& a_perColumn);
		void BuildTriangleStrip(const GLuint& a_perRow, const GLuint& a_perColumn);
		void BuildCube();
		Object* objectState;
		vec3 position, rotation, scale;
		float rotAngle, rotSpeed;

	protected:
		void LoadTriangles(GLfloat *a_vertices, GLfloat *a_uvs);
		float leftX, rightX, topY, bottomY;
		mat4 Render();
		GLuint textureID, uvID;
		GLuint numIndices, numUVs, vertexBufferID, renderMode;
};