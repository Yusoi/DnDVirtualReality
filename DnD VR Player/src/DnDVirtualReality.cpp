// DnDVirtualReality.cpp : Defines the entry point for the application.
//

#include "DnDVirtualReality.h"

using namespace std;

Engine* Engine::engine = 0;

int main(int argc, char *argv[])
{
	Engine* engine = Engine::getInstance();
	engine->setPackageFile("C:/Users/Posqg/source/repos/DnDVirtualReality/DnD VR Player/examples/Example Project/Example Package File.xml");
	engine->run(argc,argv);
	
	return 0;
}
