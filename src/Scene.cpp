#include "Scene.h"

Scene::Scene() {

}

Scene::Scene(vector<Model*> models, vector<PresetLight*> presetLights, vector<CustomLight*> customLights, vector<Texture*> textures) {
	this->models = models;
	this->presetLights = presetLights;
	this->customLights = customLights;
	this->textures = textures;
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

void Scene::addTexture(Texture* texture) {
	this->textures.push_back(texture);
}

void Scene::renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3d(-0.5, -0.5, 0.0);
	glVertex3d(0.5, 0.0, 0.0);
	glVertex3d(0.0, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}