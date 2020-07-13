#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

#include "Mesh.h"
#include "Face.h"

class ObjToVbo {
private:
	Mesh mesh;

	vector<vec3> positions_vec;
	vector<vec3> normals_vec;
	vector<vec2> textures_vec;
	vector<Face*> faces;

public:
	void import_obj_file(char* obj_path);
	void load_mesh();
	void export_vbo_file(char* project_path);
};