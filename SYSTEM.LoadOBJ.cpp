// SYSTEM.LoadOBJ.cpp
//////////////////////////////////////////////////////////////////////////

#include "SYSTEM.LoadOBJ.h"

namespace LOAD_OBJ {
	bool LoadObj(
		const char* a_path,
		std::vector<glm::vec3>& a_out_verts,
		std::vector<glm::vec2>& a_out_uvs,
		std::vector<glm::vec3>& a_out_normals				
	) {
		// Create temp variables
		std::vector<unsigned int> vertexIndices, uvIndicies, normalIndices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		// Open a file
		FILE* file = fopen(a_path, "r");
		if (file == NULL) {
			fprintf(stderr, "Impossible to open the file!\n");
			return false;
		}

		// Read the file until the end
		while(1) {
			//TODO: Check to make sure this initializes the array to zero;
			char lineHeader[128] = {0};
			// Read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if(res == EOF) break; // EOF = End Of File. Quit the loop.
			
			// Parse lineHeader
			else {
				// verts
				if (strcmp(lineHeader, "v") == 0) {
					glm::vec3 vertex;
					fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					temp_vertices.push_back(vertex);
				}
				// uvs
				else if (strcmp(lineHeader, "vt") == 0) {
					glm::vec2 uv;
					fscanf(file, "%f %f %f\n", &uv.x, &uv.y);
					temp_uvs.push_back(uv);
				}
				// normals
				else if (strcmp(lineHeader, "vn") == 0) {
					glm::vec3 normal;
					fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
					temp_normals.push_back(normal);
				}
				// faces
				else if (strcmp(lineHeader, "f") == 0) {
					string vertex1, vertex2, vertex3;
					unsigned int vertexIndex[3]={0}, uvIndex[3]={0}, normalIndex[3]={0};
					// Read in face info
					int faceInfo = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (faceInfo != 9) {
						fprintf(stderr, "File can't be read by parser.\n");
						return false;
					}
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					uvIndicies.push_back(uvIndex[0]);
					uvIndicies.push_back(uvIndex[1]);
					uvIndicies.push_back(uvIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				}
			}
		}

		// Process the data:
		// For each vertex of each triangle
		for (unsigned int i=0; i < vertexIndices.size(); ++i) {
			// index to the vertex position
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			a_out_verts.push_back(vertex);
		}
		// For each uv of each triangle
		for (unsigned int i=0; i < uvIndicies.size(); ++i) {
			// indexd to uv position
			unsigned int uvIndex = uvIndicies[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			a_out_uvs.push_back(uv);
		}
		// For each normal of each triangle
		for (unsigned int i=0; i < normalIndices.size(); ++i) {
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			a_out_normals.push_back(normal);
		}

		return true;
	}
}