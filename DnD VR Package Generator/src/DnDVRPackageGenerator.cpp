#include "DnDVRPackageGenerator.h"

int main(int argc, char* argv[]) {
	
	//Abrir menu

	

	//Conjunto de funções para dar load a um modelo, transformá-lo num formato útil e exportá-lo.
	ObjToVbo exporter;
	exporter.import_obj_file("D:/Desktop/Models/Caballero/obj/Caballero.obj");
	exporter.load_mesh();
	exporter.export_vbo_file("D:/Desktop/1.vbo");
	
	


	return 0;
}