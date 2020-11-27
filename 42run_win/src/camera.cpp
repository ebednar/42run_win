#include "camera.h"

Camera::Camera()
{
	pos = glm::vec3(0.0f, 0.0f, 3.0f);
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(pos - target);
	glm::vec3 temp_up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::normalize(glm::cross(temp_up, direction));
	up = glm::cross(direction,right);
	view = glm::lookAt(pos, pos + front, up);
	yaw = -90.0f;
	pitch = 0.0f;
	speed = 1.0f;
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	view = glm::lookAt(pos, pos + front, up);
}