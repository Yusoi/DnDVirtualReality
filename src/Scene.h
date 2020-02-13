#pragma once

#include "Model/Model.h"
#include "Light.h"
#include "Texture/Texture.h"

#include <vector>

using namespace std;

class Scene {
private:
	vector<Model*> models;
	vector<PresetLight*> presetLights;
	vector<CustomLight*> customLights;
	vector<Texture*> textures;
public:
	Scene();
	Scene(vector<Model*> models, vector<PresetLight*> presetLights, vector<CustomLight*> customLights, vector<Texture*> textures);
	void addModel(Model* model);
	void addPresetLight(PresetLight* presetLight);
	void addCustomLight(CustomLight* customLight);
	void addTexture(Texture* texture);
	void renderScene();
};
