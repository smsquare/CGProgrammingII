// SYSTEM.Mesh.cpp
//////////////////////////////////////////////////////////////////////////

#include "SYSTEM.Mesh.h"


Mesh::Mesh(void) {
	//TODO: Do I need to allocate std::vector<>?
}


Mesh::~Mesh(void) {

}

bool Mesh::LoadOBJ(const char* a_path) {
	std::vector<glm::vec3> tmp_out_verts;
	std::vector<glm::vec2> tmp_out_uvs;
	std::vector<glm::vec3> tmp_out_normals;

	bool result = LOAD_OBJ::LoadObj(a_path, tmp_out_verts, tmp_out_uvs, tmp_out_normals);

	Mesh::SetVertices(tmp_out_verts);
	Mesh::SetUVs(tmp_out_uvs);
	Mesh::SetNormals(tmp_out_normals);

	return (result) ? true : false;
}

// Get functions:
void Mesh::GetVertices(std::vector<glm::vec3>& a_verts) {
	a_verts.clear();
	for (unsigned int i=0; i < m_vertices.size(); ++i) {
		a_verts.push_back(m_vertices[i]);
	}
}

void Mesh::GetUVs(std::vector<glm::vec2>& a_uvs) {
	a_uvs.clear();
	for (unsigned int i=0; i < m_uvs.size(); ++i) {
		a_uvs.push_back(m_uvs[i]);
	}
}

unsigned int Mesh::GetNumVertexIndices() {
	unsigned int num = this->m_vertices.size();
	return num;
}

// Set functions:
void Mesh::SetVertices(std::vector<glm::vec3> a_verts) {
	this->m_vertices.clear();
	for (unsigned int i=0; i < a_verts.size(); ++i) {
		this->m_vertices.push_back(a_verts[i]);
	}
	this->m_numVertexIndices = m_vertices.size();
}

void Mesh::SetUVs(std::vector<glm::vec2> a_uvs) {
	this->m_uvs.clear();
	for (unsigned int i=0; i < a_uvs.size(); ++i) {
		this->m_uvs.push_back(a_uvs[i]);
	}
}

void Mesh::SetNormals(std::vector<glm::vec3> a_normals) {
	this->m_normals.clear();
	for (unsigned int i=0; i < a_normals.size(); ++i) {
		this->m_normals.push_back(a_normals[i]);
	}
}
