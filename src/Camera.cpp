#include "Camera.h"

Camera::Camera() {
	this->cameraPos = vec3(0.0f, 0.0f, 3.0f);
	this->cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->xzangle = 0.0f;
	this->yangle = 0.0f;
}

Camera::Camera(vec3 cameraPos, vec3 cameraTarget, vec3 up) {
	this->cameraPos = cameraPos;
	this->cameraTarget = cameraTarget;
	this->up = up;
	this->xzangle = 0.0f;
	this->yangle = 0.0f;
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

float Camera::getXZAngle() {
	return xzangle;
}

void Camera::setXZAngle(float xzangle) {
	this->xzangle = xzangle;
}

float Camera::getYAngle() {
	return yangle;
}

void Camera::setYAngle(float yangle) {
	this->yangle = yangle;
}

void Camera::lookAt() {
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			  cameraTarget.x, cameraTarget.y, cameraTarget.z,
			  up.x, up.y, up.z);
}