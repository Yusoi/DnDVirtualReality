// DnDVirtualReality.cpp : Defines the entry point for the application.
//

#include "DnDVirtualReality.h"

using namespace std;

Engine* Engine::engine = 0;

int main(int argc, char *argv[])
{
	Engine* engine = Engine::getInstance();
	engine->run(argc,argv);
	
	return 0;
}
