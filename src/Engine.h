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
		vector<Scene> scenes;

		Engine();
		void renderScene(void);
		static void renderSceneWrapper(void);
	public:
		static Engine* getInstance();
		void run(int argc, char* argv[]);
};

