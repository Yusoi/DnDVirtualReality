#include "DnDVRPackageGenerator.h"

int main(int argc, char* argv[]) {
	
	//Abrir menu

	

	//Conjunto de fun��es para dar load a um modelo, transform�-lo num formato �til e export�-lo.
	ObjToVbo exporter;
	exporter.import_obj_file("D:/Desktop/Models/Caballero/obj/Caballero.obj");
	exporter.load_mesh();
	exporter.export_vbo_file("D:/Desktop/1.vbo");
	
	


	return 0;
}