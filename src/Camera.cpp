#include "Camera.h"

Camera::Camera() {
	this->cameraPos = vec3(0.0f, 0.0f, 3.0f);
	this->cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->cameraPosDisplacement = vec3(0.0f, 0.0f, -1.0f);
	this->cameraTargetDisplacement = vec3(0.0f, 0.0f, -1.0f);
	this->angle = 0.0f;
}

Camera::Camera(vec3 cameraPos, vec3 cameraTarget, vec3 up) {
	this->cameraPos = cameraPos;
	this->cameraTarget = cameraTarget;
	this->up = up;
	this->cameraPosDisplacement = vec3(0.0f, 0.0f, -1.0f);
	this->cameraTargetDisplacement = vec3(0.0f, 0.0f, -1.0f);
	this->angle = 0.0f;
}

vec3 Camera::getCameraPos() {
	return cameraPos;
}

void Camera::setCameraPos(vec3 cameraPos) {
	this->cameraPos = cameraPos;
}

vec3 Camera::getCameraPosDisplacement() {
	return cameraPosDisplacement;
}

void Camera::setCameraPosDisplacement(vec3 cameraPosDisplacement) {
	this->cameraPosDisplacement = cameraPosDisplacement;
}

vec3 Camera::getCameraTarget() {
	return cameraTarget;
}

void Camera::setCameraTarget(vec3 cameraTarget) {
	this->cameraTarget = cameraTarget;
}

vec3 Camera::getCameraTargetDisplacement() {
	return cameraTargetDisplacement;
}

void Camera::setCameraTargetDisplacement(vec3 cameraTargetDisplacement) {
	this->cameraTargetDisplacement = cameraTargetDisplacement;
}

vec3 Camera::getUpVector() {
	return up;
}

void Camera::setUpVector(vec3 up) {
	this->up = up;
}

float Camera::getAngle() {
	return angle;
}

void Camera::setAngle(float angle) {
	this->angle = angle;
}

void Camera::lookAt() {
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			  cameraTarget.x+cameraPosDisplacement.x, cameraTarget.y, cameraTarget.z+cameraPosDisplacement.z,
			  up.x, up.y, up.z);
}