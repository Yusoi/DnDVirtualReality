#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

using namespace glm;

class Camera {
private:
	vec3 cameraPos;
	vec3 cameraTarget;
	vec3 up;
public:
	Camera();
	Camera(vec3 eye, vec3 target, vec3 up);
	void setCamera();
};