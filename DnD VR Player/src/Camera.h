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
	float xzangle;
	float yangle;
public:
	Camera();
	Camera(vec3 eye, vec3 target, vec3 up);
	void lookAt();
	vec3 getCameraPos();
	void setCameraPos(vec3 cameraPos);
	vec3 getCameraTarget();
	void setCameraTarget(vec3 cameraTarget);
	vec3 getUpVector();
	void setUpVector(vec3 up);
	float getXZAngle();
	void setXZAngle(float angle);
	float getYAngle();
	void setYAngle(float angle);
};