#include "../include/Planet.h"
#include <math.h>
#define PI 3.14159265358979323846
// Constructor
Planet::Planet(string na, float rad, float dist, float tilt, float rCol, float gCol, float bCol, float orbSpeed, float rotSpeed) {
	name = na;
	radius = rad;
	distance = dist;
	tiltAngle = tilt;
	color[0] = rCol;
	color[1] = gCol;
	color[2] = bCol;
	orbitSpeed = orbSpeed;
	rotationSpeed = rotSpeed;
	// TRẠNG THÁI MẶC ĐỊNH: Bất kể hành tinh nào vừa đẻ ra, góc quay luôn xuất phát từ 0 độ
	currentOrbitAngle = 0.0f;
	currentRotationAngle = 0.0f;
}

void Planet::drawOrrbit() {
	//Check: Không phải Mặt Trời thì mới vẽ.
	//Save : Lưu trạng thái cũ.
	//Color : Lấy bút màu xám.
	//Loop : Chạy 360 vòng, mỗi vòng tính 1 tọa độ mới rồi chấm 1 điểm.
	//Connect : OpenGL tự nối các điểm thành vòng tròn.
	//Load : Trả lại trạng thái sạch sẽ.
	if (distance <= 0.0f) return;
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float  alpha = i * PI / 180.0f;
		float x = distance * cos(alpha);
		float z = distance * sin(alpha);
		glVertex3f(x, 0.0f, z);
	}
	glEnd();
	glPopMatrix();
}

void Planet::drawPlanet() {
	// Lưu trạng thái ở gốc tọa độ
	glPushMatrix();

	// Chuyển động quỹ đạo: Xuay quanh trục Y trước r hẵng tịnh tiến ra xa
	glRotatef(currentOrbitAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(distance, 0.0f, 0.0f);

	// Độ nghiêng trục của hành tinh
	glRotatef(tiltAngle, 0.0f, 0.0f, 1.0f);

	// Tự quay quanh trục 
	glRotatef(currentRotationAngle, 0.0f, 1.0f, 0.0f);

	// Vẽ hình dáng và màu sắc
	glColor3fv(color);
	glutSolidSphere(radius, 50, 50);

	// Trả về vị trí gốc tọa độ
	glPopMatrix();
}

void Planet::updateTime() {
	// Cập nhật góc của hành tinh
	currentOrbitAngle += orbitSpeed;
	if (currentOrbitAngle >= 360.0f) {
		currentOrbitAngle -= 360.0f;
	}

	// Cập nhật góc tự xuay của hành tinh
	currentRotationAngle += rotationSpeed;
	if (currentRotationAngle >= 360.0f) {
		currentRotationAngle -= 360.0f;
	}
}
	