#include "SYSTEM.Shader.h"
#include <vector>

Shader::Shader(void) {
	m_loaded = false;
	m_result = GL_FALSE;
}


Shader::~Shader(void)
{
}

/*************************************************************
Name:	LoadShader
Params:	a_csFilePath - path to file
		a_iType		 - GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...
Result: Loads and compiles shader.
**************************************************************/
bool Shader::LoadShader(const char* a_shaderPath, int a_typeOf) {
	// Create the shader
	m_shaderID = glCreateShader(a_typeOf);
	// Read the shader code from file
	std::string strShaderCode =	ReadShaderFromFile(a_shaderPath);
	// Compile the shader
	CompileShader(strShaderCode, a_shaderPath);
	// Check the status of the shader
	if (CheckShader() == false) {
		return false;
	}

	this->m_typeOf = a_typeOf;
	this->m_loaded = true;
	return true;
}

void Shader::DeleteShader() {
	if (!IsLoaded()) return;
	this->m_loaded = false;
	glDeleteShader(this->m_shaderID);
}

std::string Shader::ReadShaderFromFile(const char* a_filePath) {
	std::string strShaderCode;
	std::ifstream shaderStream (a_filePath, std::ios::in);
	if (shaderStream.is_open()) {
		std::string Line = "";
		while (std::getline(shaderStream, Line)) {
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	return strShaderCode;
}

void Shader::CompileShader(std::string a_shaderCode, const char* a_filePath) {
	printf("Compiling shader: %\n", a_filePath);
	const char * csShaderSourcePtr = a_shaderCode.c_str();
	glShaderSource(m_shaderID, 1, &csShaderSourcePtr, NULL);
	glCompileShader(m_shaderID);
}

/************************************************************************
Name:	CheckShader
Params: None
Result: Checks the status of the shader AFTER attempting to compile.
		Logs any errors.
		Returns true or false.
************************************************************************/
bool Shader::CheckShader() {
	glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	std::vector<char> vcShaderErrorMessage(m_infoLogLength);
	glGetShaderInfoLog(m_shaderID, m_infoLogLength, NULL, &vcShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &vcShaderErrorMessage[0]);

	if (m_result == GL_FALSE) return false;
	return true;
}

bool Shader::IsLoaded() {
	return this->m_loaded;
}

GLuint Shader::GetShaderID() {
	return this->m_shaderID;
}