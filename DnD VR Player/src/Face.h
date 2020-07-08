#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <vector>
#include <iostream>

using namespace std;
using namespace glm;

class Face {
	private:
		vec3 position_index;
		vec3 texture_index;
		vec3 normal_index;
	public:
		Face();
		void add_position(vec3 index);
		void add_texture(vec3 index);
		void add_normal(vec3 index);
		vec3 get_position_index(); 
		vec3 get_texture_index();
		vec3 get_normal_index();
};
