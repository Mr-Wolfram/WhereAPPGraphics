#include "camera.h"

glm::vec3 Camera::getPosition() const {
	return position;
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + getFront(), getUp());
}


PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float znear, float zfar)
	: fovy(fovy), aspect(aspect), znear(znear), zfar(zfar) { }

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
	return glm::perspective(fovy, aspect, znear, zfar);
}


OrthographicCamera::OrthographicCamera(
	float left, float right, float bottom, float top, float znear, float zfar)
	: left(left), right(right), top(top), bottom(bottom), znear(znear), zfar(zfar) { }

glm::mat4 OrthographicCamera::getProjectionMatrix() const {
	return glm::ortho(left, right, bottom, top, znear, zfar);
}