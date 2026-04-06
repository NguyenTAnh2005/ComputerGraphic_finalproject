#pragma once

struct Camera {
	float camRadius = 80.0f;			// R của mắt (camera) --> tâm hệ tọa độ quan sát ( mặt trời, trái đất,.... Tùy TH)
	float camYaw = 0.0f;				// Góc xuay cam trái phải
	float camPitch = 0.5f;				// Góc xuay cam lên xuống  (45 độ)
	bool isPaused = false;				// Ngưng đọng Thời gian?
	bool isDragging = false;			// Đang nhấn chuột ?

	// Vị trí cuối cùng của con trỏ khi điều khiển với chuột
	int lastMouseX;
	int lastMouseY;

	void ZoomIn();
	void ZoomOut();
	// Xử lý zoom in-out khi lăn chuột và cập nhật tọa độ lastX,Y nếu nhấn chuột trái
	void handleMouseClick(int button, int state, int x, int y);

	// Đổi góc khi nhấn tọa độ lastX,Y thay đổi
	void handleMouseMotion(int x, int y);

	// Xử lý khi nhấn các phím mũi tên 
	void handleSpecialKeys(int key, int x, int y);
};




