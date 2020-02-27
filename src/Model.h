#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>

#include "Face.h"

using namespace std;
using namespace glm;

class Model {
	private:
		const char* name;
		const char *path;
		vector<vec3> vertices;
		vector<vec2> textureCoords;
		vector<vec3> normals;
		vector<Face*> faces;
	public:
		Model(char *name, char *path);
		void draw();
		void print();
};