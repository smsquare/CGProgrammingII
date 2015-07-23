#include "World.h"
#include "SYSTEM.UserInput.h"

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace{
	const u8 MAX_BUFFER_SIZE = 64;
	const u8 MAX_PATH_SIZE = 32;

	u16 GetNumCharCount(u8 *src){
		u16 count = 0;
		while(IS_NUMBER(*src)){
			++count;
			++src;
		}

		return count;
	}
}

static void FillBuffer(u8 *src, u8 *dest, u16 &index, u16 const &length){
	for(u16 i = 0, count = 0; count < length; ++i){
		if(IS_NUMBER(src[i])){
			dest[index++] = src[i];
			++count;
		}
	}
}

//TODO: Add functionality later...
World::World(){
	//cubeLarge = new Cube();


	cubeLarge = new Cube("testOBJ.txt");
	cubeLarge->SetPosition(vec3(0.0f,0.0f,0.0f));
	cubeLarge->SetRotationSpeed(0.5f);
	cubeLarge->SetScale(vec3(0.5f));

	cubeReference = new Cube("testOBJ.txt");
	cubeReference->SetPosition(vec3(0.0f,0.0f,0.0f));
	cubeReference->SetScale(vec3(0.25f));
	//cube->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	//plane = new Plane(1, 1);
	//plane->SetScale(vec3(0.15f));
	//plane->SetPosition(vec3(-1.0f, -1.0f, 0.0f));
	//GLuint textureID = plane->LoadBMP("test.bmp");
	//GLuint textureID = plane->LoadBMP("dirt.bmp");
	//GLuint textureID = plane->LoadBMP("world.bmp");

	//load world...
	ifstream myfile(LEVEL_0);

	char buffer[::MAX_BUFFER_SIZE];
	char path[::MAX_PATH_SIZE];

	if (myfile.is_open())
	{
		string line;
		unsigned char len = 0;

		bool loadLevelData = true;

		while(getline (myfile,line) )
		{
			line.copy(buffer, len = line.length());
			buffer[len] = '\0';

			if(IS_EMPTY_LINE(buffer[0])){
				continue;
			}
			else if(LOAD_TEXTURE(buffer[0])){
				//Setting buffer size...
				numTextures = buffer[1] - ASCII_ZERO;
				textureBuffer = (u8*)malloc(MAX_PATH_SIZE * numTextures);

				loadLevelData = false;
				continue;
			}
			else if(LOAD_LEVELDATA(buffer[0])){
				//Adding 1 to accomindate for comma...
				u8 numStride = ::GetNumCharCount((u8*)&buffer[1]) + 1;

				levelWidth = std::stoi(&buffer[1]);
				levelHeight = std::stoi(&buffer[1 + numStride]);

				levelBuffer = (u8*)malloc(levelWidth * levelHeight);

				loadLevelData = true;
				continue;
			}
			else if(loadLevelData){
				//TODO: May need to put this elsewhere so it doesn't persist...
				static u16 levelIndex = 0;

				//FillBuffer((u8*)buffer, levelBuffer, levelIndex, levelWidth);

				continue;
			}

			unsigned char commaLen = FindChar(buffer, ',');

			static u8 texIndex = 0;

			//numTextures = buffer[1] - ASCII_ZERO;
			//	textureBuffer = (u8*)malloc(MAX_PATH_SIZE * numTextures);

			//Found textures...
			if(commaLen > 0){
				strcpy(path, buffer);
				path[commaLen - 1] = '\0';

				memcpy(&textureBuffer[texIndex], &path, MAX_PATH_SIZE);
				texIndex += MAX_PATH_SIZE - 1;
				
				continue;
			}

			//load textures...
			//string filePath = 
		}

		myfile.close();
	}

	else cout << "Unable to open file"; 
}

unsigned char World::FindChar(const char* buffer, const char& c){
	//TODO: Search for char c, if found return true...
	char* value = (char*)buffer;
	unsigned char len = 0;

	while(value != '\0'){
		++len;
		if(*value == c){
			return len;
		}
		++value;
	}

	return len = 0;
}

//TODO: Add functionality later...
World::~World(){
	//delete plane;
	//plane = NULL;
	delete cubeLarge;
	cubeLarge = NULL;

	delete cubeReference;
	cubeReference = NULL;
}

void World::Update(const float& deltaTime){
	cubeLarge->Update(deltaTime);
	//plane->Update(deltaTime);
}

void World::UpdateCamera(Camera& camera, const float& deltaTime) {
	// TODO: Update the camera's position based on user input
	if (USERINPUT::IsKeyPressed(USERINPUT::A) || USERINPUT::IsKeyPressed(USERINPUT::D)) {
		if(USERINPUT::IsKeyPressed(USERINPUT::A)) {
			camera.angle += 50 * deltaTime;
		}
		if(USERINPUT::IsKeyPressed(USERINPUT::D)) {
			camera.angle -= 50 * deltaTime;
		}
		
		//TODO: Look into possible just subtracting off 360.0f instead of resetting to 0.0f
		if (camera.angle > 360.f) camera.angle = 0.0f;

		float radian = glm::radians(camera.angle);
		vec3 cameraPos = vec3(camera.x, camera.y, camera.z);
		// The point to rotate around
		vec3 centerPos = vec3(0,0,0);

		//float radius = glm::distance(cameraPos, centerPos);
		//TODO: Fix the hard-coded radius of 5.0f
		float x = centerPos.x + (5.0 * cosf(radian));
		float z = centerPos.z + (5.0 * sinf(radian));

		camera.x = x;
		camera.z = z;
	}

	camera.viewMatrix = glm::lookAt(
		vec3(camera.x, camera.y, camera.z),
		vec3(0,0,0),
		vec3(0,1,0)
		);
}

void World::Render(const Camera& camera){
	cubeLarge->Render(camera);
	cubeReference->Render(camera);
	//plane->Render(camera);	
}