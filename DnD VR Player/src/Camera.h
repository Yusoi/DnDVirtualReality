#pragma once

#include "stdlib.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

using namespace glm;

class Camera {
private:
	vec3 cameraPos;
	vec3 cameraTarget;
	vec3 up;
	float yaw;
	float pitch;
	int lastx;
	int lasty;

	mat4 model, view, projection;
public:
	Camera();
	Camera(vec3 eye, vec3 target, vec3 up);
	void lookAt();
	void perspective(float width, float height);
	vec3 getCameraPos();
	void setCameraPos(vec3 cameraPos);
	vec3 getCameraTarget();
	void setCameraTarget(vec3 cameraTarget);
	vec3 getUpVector();
	void setUpVector(vec3 up);
	float getYaw();
	void setYaw(int yaw);
	float getPitch();
	void setPitch(float pitch);
	int getLastX();
	void setLastX(int lastX);
	int getLastY();
	void setLastY(int lastY);
};