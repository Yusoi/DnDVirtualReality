#pragma once

#include "Model.h"
#include "Light.h"
#include "Texture.h"
#include "Actor.h"

#include <vector>

using namespace std;

class Scene {
private:
	vector<Model*> models;
	vector<Actor*> actors;
	vector<PresetLight*> presetLights;
	vector<CustomLight*> customLights;
public:
	Scene();
	Scene(vector<Model*> models, vector<PresetLight*> presetLights, vector<CustomLight*> customLights);
	void addModel(Model* model);
	void addPresetLight(PresetLight* presetLight);
	void addCustomLight(CustomLight* customLight);
	void renderScene();
};
