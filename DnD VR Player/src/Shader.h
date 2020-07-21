#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "IL/il.h"
#include "glm/glm.hpp"

using namespace std;

class Shader {
private:
	GLuint vShader_id;
	GLuint fShader_id;
	GLuint program_id;

public:
	Shader(string vShader_path, string fShader_path);
	GLuint getProgramId();
};