// SYSTEM.Mesh.h
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Application.h"
#include "SYSTEM.LoadOBJ.h"
#include <vector>

class Mesh {
	public:
		Mesh(void);
		~Mesh(void);

		bool LoadOBJ(const char* a_path);

		void GetVertices(std::vector<glm::vec3>& a_verts);
		void GetUVs(std::vector<glm::vec2>& a_uvs);
		unsigned int GetNumVertexIndices();

		void SetVertices(std::vector<glm::vec3> a_verts);
		void SetUVs(std::vector<glm::vec2> a_uvs);
		void SetNormals(std::vector<glm::vec3> a_normals);
		
	private:
		std::vector<unsigned int> m_vertexIndices, m_uvIndices, m_normalIndices;
		unsigned int m_numVertexIndices;
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
};

