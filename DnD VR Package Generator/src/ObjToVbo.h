#include <iostream>
#include "Mesh.h"

class ObjToVbo {
private:
	string path;
	Mesh mesh;
public:
	void loadVertex();
	void import_obj_file(string path);
	void export_vbo_file(string project_path);

};