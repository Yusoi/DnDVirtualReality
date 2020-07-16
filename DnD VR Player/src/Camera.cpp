#include "Camera.h"

Camera::Camera() {
	this->cameraPos = vec3(0.0f, 0.0f, 3.0f);
	this->cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	vec3 frontVec = cameraTarget - cameraPos;
	this->yaw = -45.0f;
	this->pitch = 0.0f;
	this->lastx = 400;
	this->lasty = 400;
}

Camera::Camera(vec3 cameraPos, vec3 cameraTarget, vec3 up) {
	this->cameraPos = cameraPos;
	this->cameraTarget = cameraTarget;
	this->up = vec3(0.0f, 1.0f, 0.0f);
	vec3 frontVec = cameraTarget - cameraPos;
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->lastx = 400;
	this->lasty = 400;
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
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			  cameraTarget.x, cameraTarget.y, cameraTarget.z,
			  up.x, up.y, up.z);
}