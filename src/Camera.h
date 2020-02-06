#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

class Camera {
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 up;
public:
	Camera();
	Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	void setCamera();
};