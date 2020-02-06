#include "Camera.h"

Camera::Camera() {
	this->cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	this->cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 up) {
	this->cameraPos = cameraPos;
	this->cameraTarget = cameraTarget;
	this->up = up;
}

void Camera::setCamera() {
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
			  cameraTarget.x, cameraTarget.y, cameraTarget.z,
			  up.x, up.y, up.z);
}