#pragma once


#include "stdlib.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "IL/il.h"

#include "Scene.h"

#include <vector>

using namespace std;

class Engine {
	private:
		static Engine *engine;
		Scene *scene;

		Engine();
	public:
		static Engine* getInstance();
		void run(int argc, char* argv[]);
		void renderScene();
		static void renderSceneWrapper();
		void processNormalKeys(unsigned char key, int x, int y);
		void processSpecialKeys(int key, int x, int y);
};

