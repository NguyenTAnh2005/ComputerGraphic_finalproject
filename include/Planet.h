#pragma once
#include <string>
#include <GL/glut.h>
using namespace std;
  
class Planet {
public:
	string name;				// PLanet name
	float radius;				// Planet radius
	float distance;				// Distance from the sun
	float tiltAngle;			// Độ nghiêng trục của hành tinh
	float color[3];				// RGB color
	float orbitSpeed; 			// Speed of orbiting around the sun
	float rotationSpeed; 		// Speed of rotation around its own axis
	float currentOrbitAngle;    // Góc quỹ đạo HIỆN TẠI đang ở đâu (0 đến 360 độ)
	float currentRotationAngle; // Góc tự quay HIỆN TẠI đang ở đâu

	// Hàm khởi tạo constructor
	Planet(string na, float rad, float dist, float tilt,
		float rCol, float gCol, float bCol, // Màu sắc RGB cho biến color
		float orbSpeed, float rotSpeed
	);

	// Các Phương thức
	void drawOrrbit();		// Vẽ quỹ đạo
	void drawPlanet();		// Vẽ hành tinh
	void updateTime();		// Tính toán góc quay cho khung hình tiếp theo
};