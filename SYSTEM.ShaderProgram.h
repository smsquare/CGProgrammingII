// SYSTEM.ShaderProgram.h
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "SYSTEM.Shader.h"

class ShaderProgram {
	public:
		ShaderProgram(void);
		~ShaderProgram(void);

		void CreateProgram();
		void DeleteProgram();

		bool AddShaderToProgram(Shader* a_shader);
		bool LinkProgram();
		void UseProgram();

		GLuint GetProgramID();
	private:
		GLuint m_programID;		// ID of program
		bool m_linked;			// Whether program is linked and ready to use.
};

