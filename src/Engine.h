#pragma once


#include "stdlib.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "IL/il.h"

#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "Texture.h"
#include "Actor.h"

#include <filesystem>
#include <vector>

using namespace std;

class Engine {
	private:
		static Engine* engine;
		Camera* camera;

		vector<Model*> models;
		vector<Actor*> actors;
		vector<PresetLight*> presetLights;
		vector<CustomLight*> customLights;

		Engine();
	public:
		static Engine* getInstance();
		void renderScene();
		static void renderSceneWrapper();
		void reshapeWindow(int w, int h);
		static void reshapeWindowWrapper(int w, int h);
		void processNormalKeys(unsigned char key, int x, int y);
		static void processNormalKeysWrapper(unsigned char key, int x, int y);
		void processSpecialKeys(int key, int x, int y);
		static void processSpecialkeysWrapper(int key, int x, int y);
		void addModel(Model* model);
		void addPresetLight(PresetLight* presetLight);
		void addCustomLight(CustomLight* customLight);
		void loadModels();
		void run(int argc, char* argv[]);
};

