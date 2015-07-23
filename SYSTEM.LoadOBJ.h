// SYSTEM.LoadOBJ.h
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "Application.h"
#include <vector>

namespace LOAD_OBJ {
	bool LoadObj(
		const char* a_path,
		std::vector<glm::vec3>& a_out_verts,
		std::vector<glm::vec2>& a_out_uvs,
		std::vector<glm::vec3>& a_out_normals				
	);
}