#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

#include "Model.h"

#define INACTIVE_THRESHOLD 5

class Actor {
private:
	Model* model;
	string actor_id;
	string actor_name;
	pair<int, int> pos = { 0,0 };
	int inactive_counter;
public:
	Actor(Model* model, string actor_id, string actor_name);
	Model* getModel();
	void setPos(pair<int, int> pos);
	void draw();
	void incrementInactiveCounter();
	void resetInactiveCounter();
};