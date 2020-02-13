#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include <string>

using namespace glm;

class Light {
	protected:
		vec4 l_pos;
		vec4 l_dir;
		vec4 l_color;
};

class PresetLight: public Light {
	private:
		char* preset;
	public:
		PresetLight();
		PresetLight(vec4 l_pos, vec4 l_dir, vec4 l_color, char* preset);
};

class CustomLight : public Light {
	public:
		CustomLight();
		CustomLight(vec4 l_pos, vec4 l_dir, vec4 l_color);
};