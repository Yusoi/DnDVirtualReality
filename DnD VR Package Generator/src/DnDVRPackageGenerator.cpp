#include "DnDVRPackageGenerator.h"

int main(int argc, char* argv[]) {
	
	//TODO:Abrir menu

	//Conjunto de fun��es para dar load a um modelo, transform�-lo num formato �til e export�-lo.
	ObjToVbo exporter;
	exporter.import_obj_file("D:/Desktop/back_wall.obj");
	exporter.load_mesh();
	exporter.export_vbo_file("C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/res/models/back_wall.vbo");

	return 0;
}