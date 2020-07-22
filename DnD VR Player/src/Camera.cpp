#include "Camera.h"

Camera::Camera() {
	this->cameraPos = vec3(0.0f, 0.0f, 3.0f);
	this->cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	vec3 frontVec = cameraTarget - cameraPos;

	this->yaw = atan2(frontVec.x, frontVec.z); 
	this->pitch = atan2(frontVec.y, sqrt((frontVec.x * frontVec.x) 
										+ (frontVec.z * frontVec.z)));
	this->lastx = 400;
	this->lasty = 400;

	model = mat4(1.0f);
}

Camera::Camera(vec3 cameraPos, vec3 cameraTarget, vec3 up) {
	this->cameraPos = cameraPos;
	this->cameraTarget = cameraTarget;
	this->up = vec3(0.0f, 1.0f, 0.0f);
	vec3 frontVec = cameraTarget - cameraPos;
	this->yaw = atan2(frontVec.x, frontVec.z);
	this->pitch = atan2(frontVec.y, sqrt((frontVec.x * frontVec.x)
		+ (frontVec.z * frontVec.z)));
	this->lastx = 400;
	this->lasty = 400;

	model = mat4(1.0f);
}

vec3 Camera::getCameraPos() {
	return cameraPos;
}

void Camera::setCameraPos(vec3 cameraPos) {
	this->cameraPos = cameraPos;
}

vec3 Camera::getCameraTarget() {
	return cameraTarget;
}

void Camera::setCameraTarget(vec3 cameraTarget) {
	this->cameraTarget = cameraTarget;
}

vec3 Camera::getUpVector() {
	return up;
}

void Camera::setUpVector(vec3 up) {
	this->up = up;
}

float Camera::getYaw() {
	return yaw;
}

void Camera::setYaw(int yaw) {
	this->yaw = yaw;
}

float Camera::getPitch() {
	return pitch;
}

void Camera::setPitch(float pitch) {
	this->pitch = pitch;
}

int Camera::getLastX() {
	return lastx;
}

void Camera::setLastX(int lastx) {
	this->lastx = lastx;
}

int Camera::getLastY() {
	return lasty;
}

void Camera::setLastY(int lasty) {
	this->lasty = lasty;
}

void Camera::lookAt() {
	//view = glm::lookAt(cameraPos, cameraTarget, up);
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			 cameraTarget.x, cameraTarget.y, cameraTarget.z,
			 up.x, up.y, up.z);
}

void Camera::perspective(float width, float height) {
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}