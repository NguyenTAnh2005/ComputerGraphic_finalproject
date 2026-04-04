#pragma once

#include <string>
#include <vector>
#include <GL/glut.h>
#include <cmath>

using namespace std;
struct RealSpaceData {
	string name;
	double radiusKM;	// Bán kính - KM
	double distAU;		// khoảng cách đơn vị thiên văn
	float tilt;
	float color[3];
	double dayHours;		// Giờ / Ngày --> Ám chỉ tốc độ tự quay quanh trục
	double yearDays;		// Chu kỳ quay quanh mặt trời 
	bool hasRing;
	GLuint textureID;
};


class Planet {
private:
	string name;				// PLanet name
	float radius;				// Planet radius
	float distance;				// Distance from the sun
	float tiltAngle;			// Độ nghiêng trục của hành tinh
	float color[3];				// RGB color
	float orbitSpeed; 			// Speed of orbiting around the sun
	float rotationSpeed; 		// Speed of rotation around its own axis
	float currentOrbitAngle;    // Góc quỹ đạo HIỆN TẠI đang ở đâu (0 đến 360 độ)
	float currentRotationAngle; // Góc tự quay HIỆN TẠI đang ở đâu
	bool hasRing;				// Có vành đai ?

	vector <Planet> moons;

	GLuint textureID;			// Biến mới để lưu ID tấm ảnh sau khi load

public:
	// Hàm khởi tạo constructor - nhận các thông số đã chuẩn hóa
	Planet(string na, float rad, float dist, float tilt,
		float rCol, float gCol, float bCol, // Màu sắc RGB cho biến color
		float orbSpeed, float rotSpeed, bool ring, GLuint textureid
	);
	// Hàm biến đổi giá trị ở struct RAW --> Object chứa các GT chuẩn hóa 
	static Planet createFromRealData(RealSpaceData data);
	
	// Các Phương thức
	void drawOrrbit();		// Vẽ quỹ đạo
	void drawPlanet();		// Vẽ hành tinh
	void updateTime();		// Tính toán góc quay cho khung hình tiếp theo

	// Get planet position
	void getPosition(float& x, float& y, float& z);

	// Thêm moons cho hành tinh 
	void addMoon(Planet m) {
		moons.push_back(m);
	};
};