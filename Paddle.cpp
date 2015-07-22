#include "Paddle.h"

Paddle::Paddle() : Object(){
	BuildTriangles(2, 0);
	//BuildTriangleStrip(2, 0);
	SetScale(vec3(0.025f, 0.25f, 1.0f));
	upKey = NO_KEY;
	downKey = NO_KEY;
}

Paddle::~Paddle(){

}

void Paddle::Update(const float& deltaTime){
	if(glfwGetKey(window, upKey) == GLFW_PRESS)
		SetPosition(position + vec3(0.0f, 1.0f * deltaTime, 0.0f));
	else if(glfwGetKey(window, downKey) == GLFW_PRESS)
		SetPosition(position + vec3(0.0f, -1.0f * deltaTime, 0.0f));

	Object::Update(deltaTime);
}

void Paddle::SetKeys(const int& upKey, const int&downKey){
	this->upKey = upKey;
	this->downKey = downKey;
}