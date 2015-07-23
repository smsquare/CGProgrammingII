// SYSTEM.Shader.h
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Application.h"

class Shader {
	public:
		Shader(void);
		~Shader(void);
	public:
		bool LoadShader(const char* a_shaderPath, int a_typeOf);
		void DeleteShader();
		std::string ReadShaderFromFile(const char* a_filePath);
		
		void CompileShader(std::string a_shaderCode, const char* a_filePath);
		bool CheckShader();

		bool IsLoaded();
		GLuint GetShaderID();

	private:
		GLuint m_shaderID;		// ID of shader
		int m_typeOf;			// GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
		bool m_loaded;			// Whether shader was loaded and compiled
		int m_infoLogLength;	// Length of log used during shader processing
		GLint m_result;			// Used in checking shader status
};

