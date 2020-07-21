#pragma once


#include "stdlib.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "IL/il.h"
#include "glm/glm.hpp"

#include "Camera.h"
#include "Model.h"
#include "Light.h"
#include "Actor.h"
#include "Tile.h"
#include "Shader.h"
#include "PackageReader.h"
#include "ImageInterpreter.h"

#include <filesystem>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

using namespace std;

class Engine {
	private:
		static Engine* engine;
		Camera* camera;
		Shader* shader;

		string packagefile_path;

		map<string,Model*> models;
		map<string,Actor*> actors;
		vector<Tile*> tiles;
		map<string,Model*> tile_models;
		vector<PresetLight*> presetLights;
		vector<CustomLight*> customLights;
		pair<int, int> boardsize;

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
		void mouseButton(int button, int state, int x, int y);
		static void mouseButtonWrapper(int button, int state, int x, int y);
		void mouseMove(int x, int y);
		static void mouseMoveWrapper(int x, int y);
		
		

		void addModel(Model* model);
		void addPresetLight(PresetLight* presetLight);
		void addCustomLight(CustomLight* customLight);
		void setPackageFile(string packagefile_path);
		void loadModels();

		void loadShaders();

		void run(int argc, char* argv[]);
};

