#pragma once

#include "Model/Model.h"
#include "Light.h"
#include "Texture/Texture.h"

#include <vector>

using namespace std;

class Scene {
private:
	vector<Model*> models;
	vector<Light*> lights;
	vector<Texture*> textures;
public:
	Scene();
	void renderScene();
};
