#include "Object.h"
#include "Plane.h"
#include "Ball.h"
#include "Paddle.h"
#include "Cube.h"

#pragma once

#define ASCII_ZERO 48

#define LOAD_TEXTURE(chr) (chr == 35)
#define LOAD_LEVELDATA(chr) (chr == 40)
#define IS_NUMBER(chr) (chr > 47 && chr < 58)
#define IS_EMPTY_LINE(chr) (chr == 32 || chr == '\0')

#define LEVEL_0 "level_0.txt"

class World{

	public:
		World();
		virtual ~World();

		void Update(const float& deltaTime);
		void UpdateCamera(Camera& camera, const float& deltaTime);
		void Render(const Camera& camera);

	private:
		unsigned char FindChar(const char* buffer, const char& c);
		
	private:
		Plane* plane;
		Cube* bunnyMesh;
		Cube* cubeReference;
		u8* levelBuffer;
		u8* textureBuffer;
		u8 numTextures, levelWidth, levelHeight;
};