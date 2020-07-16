#include "Tile.h"


Tile::Tile(pair<int, int> pos, int code) {
	this->pos = pos;
	this->code = code;
}

int Tile::getCode() {
	return code;
}

void Tile::addModel(Model* model) {
	models.push_back(model);
}

void Tile::draw() {
	glPushMatrix();
		glTranslatef(float(pos.first)*2, 0.0f, float(pos.second)*2);
		for (vector<Model*>::iterator it = models.begin(); it != models.end(); it++) {
			((Model*)*it)->drawVAO();
		}
		glTranslatef(0.0f, 2.0f, 0.0f);
		for (vector<Model*>::iterator it = ++models.begin(); it != models.end(); it++) {
			((Model*)*it)->drawVAO();
		}
	glPopMatrix();
}