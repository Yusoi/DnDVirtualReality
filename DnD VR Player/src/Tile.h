#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <string>

#include "Model.h"

using namespace std;
using namespace glm;

class Tile{
private:
	pair<int, int> pos; 
	int code;
	vector<Model*> models;
public:
	Tile(pair<int, int> pos, int code);
	int getCode();
	void addModel(Model* model);
	void draw();

};