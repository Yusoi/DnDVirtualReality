#include "Scene.h"

Scene::Scene() {
	//Import all default stuff
	Model* barrel = new Model("Object", "D:/Desktop/Universidade/Visualização e Iluminação I/Aula 9/metal_barrel/metal_barrel.obj");
	models.push_back(barrel);
}

Scene::Scene(vector<Model*> models, vector<PresetLight*> presetLights, vector<CustomLight*> customLights) {
	this->models = models;
	this->presetLights = presetLights;
	this->customLights = customLights;
}

void Scene::addModel(Model* model) {
	this->models.push_back(model);
}

void Scene::addPresetLight(PresetLight* presetLight) {
	this->presetLights.push_back(presetLight);
}

void Scene::addCustomLight(CustomLight* customLight) {
	this->customLights.push_back(customLight);
}

void Scene::renderScene(void) {
	
	glClearColor(0.1f,0.3f,0.5f,0.3f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	cout << "Models size: " << models.size() << "\n";

	for(vector<Model*>::iterator it = models.begin(); it < models.end(); ++it) {
		cout << "In" << "\n";
		(*it)->draw();
	}

	glutSwapBuffers();
}