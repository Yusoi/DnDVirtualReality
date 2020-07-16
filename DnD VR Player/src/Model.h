#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "IL/il.h"
#include "glm/glm.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <iostream>

using namespace std;
using namespace glm;

class Model {
	private:
		const char* name;
		const char* obj_path;
		const char* tex_path;

		GLuint m_VAO;		 //VAO
		GLuint m_buffers[4]; //Buffer 1-Positions 2-Normals 3-TexCoords 4-Indices
		int buffer_size[4]; //Buffer Size 1-Positions 2-Normals 3-TexCoords 4-Indices

		GLuint tex_buffer;
		float* positions_array, * textures_array, * normals_array;
		int* indexes_array;

	public:
		Model(char *name, char *obj_path, char *tex_path);
		void load_model(char* obj_path);
		void load_texture(char* tex_path);
		void prepare_vao();
		void drawVAO();
		void draw();
		void print();
		string getName();
};