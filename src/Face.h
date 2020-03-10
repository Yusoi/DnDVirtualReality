#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <vector>

using namespace std;
using namespace glm;

class Face {
	private:
		vector<int> position_index;
		vector<int> texture_index;
		vector<int> normal_index;
		int type;
	public:
		Face(int type);
		void add_position(int index);
		void add_texture(int index);
		void add_normal(int index);
		vector<int>* get_position_index(); 
		vector<int>* get_texture_index();
		vector<int>* get_normal_index();
		int getType();
		int size();
};
