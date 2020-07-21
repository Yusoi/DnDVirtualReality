#include "Actor.h"

Actor::Actor(Model* model, string actor_id, string actor_name) {
	this->model = model;
	this->actor_id = actor_id;
	this->actor_name = actor_name;
	this->inactive_counter = INACTIVE_THRESHOLD;
}

Model* Actor::getModel() {
	return model;
}

void Actor::setPos(pair<int, int> pos) {
	this->pos = pos;
}

void Actor::draw() {
	if (inactive_counter < INACTIVE_THRESHOLD) {
		glPushMatrix();
			glTranslatef(float(pos.first), 0.0f, float(pos.second));
			model->drawVAO();
		glPopMatrix();
	}
}

void Actor::incrementInactiveCounter() {
	inactive_counter++;
}

void Actor::resetInactiveCounter() {
	inactive_counter = 0;
}