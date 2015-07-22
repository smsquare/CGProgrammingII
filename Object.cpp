#include "Object.h"
#include "Matrix.h"

Object::Object(){
	objectState = NULL;
	renderMode = GL_TRIANGLES;
	vertexBufferID = 0;
	SetPosition(vec3(0));
	SetScale(vec3(1));
	numIndices = 6;
	numUVs = 0;
	textureID = 0;
	rotSpeed = 0;
}

Object::~Object(){
	
}

void Object::SetPosition(vec3 a_position){
	this->position = a_position;
}

void Object::SetRotationSpeed(float a_rotSpeed) {
	this->rotSpeed = a_rotSpeed;
}

void Object::SetScale(vec3 a_scale){
	this->scale = a_scale;
}

vec3 Object::GetPosition(){
	return position;
}

float Object::GetLeftX(){
	return leftX;
}

float Object::GetRightX(){
	return rightX;
}

float Object::GetTopY(){
	return topY;
}

float Object::GetBottomY(){
	return bottomY;
}

void Object::Update(const float& a_deltaTime){
	leftX = position.x - scale.x;
	rightX = position.x + scale.x;
	topY = position.y + scale.y;
	bottomY = position.y - scale.y;

	rotAngle += rotSpeed * a_deltaTime;
}

void Object::Render(const Camera& a_camera){
	mat4 modelMatrix = Render();
	mat4 MVPMatrix = a_camera.projectionMatrix * a_camera.viewMatrix * modelMatrix;

	glUniformMatrix4fv(a_camera.MVPMatrixID, 1, GL_FALSE, &MVPMatrix[0][0]);
}

void Object::BuildTriangles(const GLuint& a_perRow, const GLuint& a_perColumn){
	int numValuesPerRow = 18 * a_perRow;
	int numValues = 18 * a_perRow * a_perColumn;

	GLfloat *vertices = new GLfloat[numValues];
	for(int i = 0, x = 0, y = 0; i < numValues; ++x){
		vertices[i] = x;		vertices[++i] = y + 1;	vertices[++i] = 0;
		vertices[++i] = x;		vertices[++i] = y;		vertices[++i] = 0;
		vertices[++i] = x + 1;	vertices[++i] = y + 1;	vertices[++i] = 0;
		
		vertices[++i] = x + 1;	vertices[++i] = y;		vertices[++i] = 0;
		vertices[++i] = x + 1;	vertices[++i] = y + 1;	vertices[++i] = 0;
		vertices[++i] = x;		vertices[++i] = y;		vertices[++i] = 0;

		if(++i % numValuesPerRow == 0){
			x = -1; --y;
		}
	}

	int numUvValuesPerRow = 12 * a_perRow;
	int numUvValues = 12 * a_perRow * a_perColumn;

	GLfloat *uvs = new GLfloat[numUvValues];
	for(int i = 0, u = 0, v = 0; i < numUvValues; ++u){
		uvs[i] = u + 0.625f;	uvs[++i] = -v - 0.9166;
		uvs[++i] = u + 0.625f;	uvs[++i] = -v - 1;
		uvs[++i] = u + 0.6875f;		uvs[++i] = -v - 0.9166;
		
		uvs[++i] = u + 0.6875f;		uvs[++i] = -v - 1;
		uvs[++i] = u + 0.6875f;		uvs[++i] = -v - 0.9166;
		uvs[++i] = u + 0.625f;	uvs[++i] = -v - 1;

		if(++i % numUvValuesPerRow == 0){
			u = -1; ++v;
		}
	}

	//0,1	
	//0,0	

	//U: 0.625 - 0.0625			0.625
	//V: 1 - 0.0833				0.625 - 0.0833	

	//U: 0.625 - 0.0625			0.625
	//V: 1						1 		

	numUVs = numUvValues/2;
	numIndices = numValues/3;
	this->renderMode = GL_TRIANGLES;
	LoadTriangles(vertices, uvs);
}

void Object::BuildTriangleStrip(const GLuint& a_perRow, const GLuint& a_perColumn){
	/*
		0, 1	1, 1	|	2, 1	3, 1
		0, 0	1, 0	|	2, 0	3, 0
						|
		0, 0	1, 0	|	2, 0 	3, 0
		0,-1	1,-1	|	2,-1	3,-1
	*/

	int numValuesPerRow = (2 + (2 * a_perRow)) *3, numDegenValues = 2 * 3;
	uint numValues = (numValuesPerRow + numDegenValues) * a_perColumn;

	GLfloat *vertices = new GLfloat[numValues];
	for(int i = 0, x = 0, y = 0; i < numValues; ++x){
		vertices[i] = x;		vertices[++i] = y + 1;	vertices[++i] = 0;
		vertices[++i] = x;		vertices[++i] = y;		vertices[++i] = 0;

		if((++i) % numValuesPerRow == 0){
			vertices[i] = x;	vertices[++i] = y;	vertices[++i] = 0;
			vertices[++i] = x;		vertices[++i] = y;	vertices[++i] = 0;
			numValuesPerRow += numDegenValues;
			i +=1;
			x = -1; --y;
		}
	}

	/*GLfloat *vertices = new GLfloat[numVertices];
	vertices[0] = 0.0f; vertices[1] = 1.0f; vertices[2] = 0.0f;
	vertices[3] = 0.0f; vertices[4] = 0.0f; vertices[5] = 0.0f;
	vertices[6] = 1.0f; vertices[7] = 1.0f; vertices[8] = 0.0f;
	vertices[9] = 1.0f; vertices[10] = 0.0f; vertices[11] = 0.0f;

	vertices[12] = 1.0f; vertices[13] = 0.0f; vertices[14] = 0.0f;
	vertices[15] = 1.0f; vertices[16] = 0.0f; vertices[17] = 0.0f;

	vertices[18] = 0.0f; vertices[19] = 0.0f; vertices[20] = 0.0f;
	vertices[21] = 0.0f; vertices[22] = -1.0f; vertices[23] = 0.0f;
	vertices[24] = 1.0f; vertices[25] = 0.0f; vertices[26] = 0.0f;
	vertices[27] = 1.0f; vertices[28] = -1.0f; vertices[29] = 0.0f;*/

	numIndices = numValues/3;
	this->renderMode = GL_TRIANGLE_STRIP;
	LoadTriangles(vertices, vertices);
}

void Object::BuildCube() {
	

	this->renderMode = GL_TRIANGLES;

	
}

void Object::LoadTriangles(GLfloat *a_vertices, GLfloat *a_uvs){
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, numIndices * 3 * sizeof(GLfloat), a_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &uvID);
	glBindBuffer(GL_ARRAY_BUFFER, uvID);
	glBufferData(GL_ARRAY_BUFFER, numUVs * 2 * sizeof(GLfloat), a_uvs, GL_STATIC_DRAW);
}

void Object::SaveObjectState(char *a_message){
	if(objectState == NULL)
		objectState = (Object*)malloc(sizeof(*this));

	*objectState = *this;
	puts(a_message);
}

void Object::LoadObjectState(char *a_message){
	*this = *objectState;
	puts(a_message);
}

GLuint Object::LoadBMP(const char * a_imagepath){
	// Data read from the header of the BMP file
	unsigned char header[54];	// Each BMP file begins by a 54-bytes header
	unsigned int dataPos;		// Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;		// = width*height*3
	unsigned char * data;		// Actual RGB data

	// Open the file
	const char* mode = "rb";
	FILE * file = fopen(a_imagepath, mode);
	if (!file){
		printf("Image could not be opened\n");
		return 0;
	}

	// If not 54 bytes read : problem
	if(fread(header, 1, 54, file)!=54 ){	
		printf("Not a correct BMP file\n");
		return false;
	}

	//Checking to see if first two bytes are 'B' and 'M'
	if ( header[0] != 'B' || header[1] != 'M' ){
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if(imageSize==0)    
		imageSize=width*height*3;	// 3 : one byte for each Red, Green and Blue component
	if(dataPos==0)
		dataPos=54;					// The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];
 
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
 
	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	glGenTextures(1, &textureID);
 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
 
	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

mat4 Object::Render(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glVertexAttribPointer(
		0,			//attribute layout
		3,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

	//Rendering UVs...
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvID);

	glVertexAttribPointer(
		1,			//attribute layout
		2,			//Elements in array
		GL_FLOAT,	//Each element is of type float
		GL_FALSE,	//Normalized?
		0,			//Stride...
		(void*)0	//Array buffer offset...
	);

	glDrawArrays(renderMode, 0, numIndices);	//GL_TRIANGLE_STRIP or GL_TRIANGLES

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//Every object starts off with an identity matrix...
	/*mat4 objectMatrix = mat4(1.0f);
	mat4 identityMatrix = glm::scale(objectMatrix, scale);	
	mat4 modelMatrix = translate(identityMatrix, position);*/

	mat4 identityMatrix = mat4(1.0f);
	mat4 scaleMatrix = glm::scale(identityMatrix, vec3(scale));
	mat4 translateMatrix = translate(identityMatrix, position);
	mat4 rotationMatrix = glm::rotate(identityMatrix, this->rotAngle, this->rotation);
	mat4 modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
		//glm::scale(translateMatrix, scale);

	return modelMatrix;
}

//static mat4 Render(GLuint vertexBuffer, const vec3& position, const vec3& scale);