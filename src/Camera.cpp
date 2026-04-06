#include "../include/Camera.h"
#include <GL/glut.h>
float minCamradius = 1.5f;
float maxCamradius = 150.0f;

// Các hàm xử lý cho góc quay Camera
// 
// Phóng to
void Camera::ZoomIn() {
	camRadius -= 1.5f;
	if (camRadius < minCamradius) { camRadius = minCamradius; }
}
// Thu nhỏ
void Camera::ZoomOut() {
	camRadius += 1.5f;
	if (camRadius > maxCamradius) { camRadius = maxCamradius; }
}
// Xử lý zoom in-out khi lăn chuột và cập nhật tọa độ lastX,Y nếu nhấn chuột trái
void Camera::handleMouseClick(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == 3) ZoomIn();
		else if (button == 4) ZoomOut();
	}
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDragging = true;
			lastMouseX = x;
			lastMouseY = y;
		}
		else if (state == GLUT_UP) {
			isDragging = false;
		}
	}
}

// Đổi góc khi nhấn tọa độ lastX,Y thay đổi
void Camera::handleMouseMotion(int x, int y) {
	if (isDragging) {
		int delX = x - lastMouseX;
		int delY = y - lastMouseY;

		float sensitivity = 0.005f; // độ nhạy chuột 1 pixel tương ứng bao nhiêu rad 

		camPitch += delY * sensitivity;
		camYaw += delX * sensitivity;

		if (camPitch > 1.5f) camPitch = 1.5f;
		if (camPitch < -1.5f) camPitch = -1.5f;

		lastMouseX = x;
		lastMouseY = y;
	}
}

// Xử lý khi nhấn các phím mũi tên 
void Camera::handleSpecialKeys(int key, int x, int y) {
	const float angleSpeed = 0.05f; // Độ quay 1 lần ( Radian )
	switch (key) {
	case GLUT_KEY_LEFT: camYaw -= angleSpeed; break;
	case GLUT_KEY_RIGHT: camYaw += angleSpeed; break;
	case GLUT_KEY_UP:
		camPitch += angleSpeed;
		// chặn camera ko bị lật ngược
		// 1.5 rad ~ 85.94 độ, nếu set giới hạn gần hoặc bằng 90 độ dễ gây ra sự rối loạn của các vector up và look at
		if (camPitch > 1.5f) { camPitch = 1.5f; }
		break;
	case GLUT_KEY_DOWN:
		camPitch -= angleSpeed;
		if (camPitch < -1.5f) { camPitch = -1.5f; }
		break;
	}
}


