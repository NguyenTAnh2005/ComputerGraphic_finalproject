#include "../include/Planet.h"
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

// Hàm biến đổi từ giá trị thực ở Struct sang OBJect với GT chuẩn hóa 
Planet Planet::createFromRealData(RealSpaceData data) {
	// 1. Định nghĩa các chuẩn 
	const float EARTH_RAD_KM = 6371.0f;		// bán kính km của trái đất
	const float EARTH_DIST_AU = 1.0f;		// D từ trái đất đến mặt trời = 1 đơn vị thiên văn ~ 150M km
	const float EARTH_DAY_HOURS = 24.0f;	// Chu kỳ tự quay của Trái đất = 24h  -- Rotation Speed
	const float EARTH_YEARS_DAY = 365.25f;	// Chu kỳ quay quanh mặt trời = 365 ngày 6 hours -- OrbitSpeed 

	// 2. Các chuẩn 1 được chuẩn hóa tại Open GL 
	const float EARTH_RAD_GL = 0.4f;		// Trái đất to 0.4
	const float EARTH_DIST_GL = 6.0f;		// Trái đất cách mặt trời 0.6
	const float EARTH_ROT_SPEED_GL = 1.0f;	// Trái đất tự quay với tốc độ = 1
	const float EARTH_ORB_SPEED_GL = 0.7f;	// Trái đất bay với tốc độ 0.7 đơn vị góc / frame

	// 3. Tính toán chuẩn hóa 
	
	float resDist = (data.distAU == 0) ? 0.0f : sqrt(data.distAU / EARTH_DIST_AU) * EARTH_DIST_GL;

	// Nếu dùng CT của Wiki thì tỉ lệ lệch khá nhiều, không đủ vẽ
	// --> Clamp 1.5 là sun max, 1.1 cho sao mộc (nhỏ hơn mỗi mặt trời)
	// Tạo ra sự phân cấp và đảm bảo các hành tinh ko quá nhỏ
	float resRad = (data.radiusKM / EARTH_RAD_KM) * EARTH_RAD_GL;
	if (data.name == "Sun") {resRad = 1.75f;}
	else if (resRad > 1.3f) { resRad = 1.3f; }

	float resOrbSpeed = (data.distAU == 0) ? 0.0f : (EARTH_YEARS_DAY/data.yearDays) * EARTH_ORB_SPEED_GL;

	float resRotSpeed = (EARTH_DAY_HOURS / data.dayHours) * EARTH_ROT_SPEED_GL;

	return Planet(data.name, resRad, resDist, data.tilt,
				  data.color[0], data.color[1], data.color[2],
				  resOrbSpeed,resRotSpeed);
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
	// Lưu vị trí mặt trời 
	glPushMatrix();

	// Xuay hành tinh quanh trục Y rồi đưa ra quỹ đạo
	glRotatef(currentOrbitAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(distance, 0.0f, 0.0f);

	// Vẽ mặt trăng, do chưa glPopMatrix nên hiện tại tâm tọa độ chính là hành tinh 
	for (int index = 0; index < moons.size(); index++) {
		// Xuay mặt trăng quanh trục y tại tâm rồi tịnh tiến ra quỹ đạo
		// biến radius ban đầu là D của hành tinh --> The Sun thì bây giờ là D từ mặt trăng đến hành tinh 
		// Tuy nhiên bản chất hàm drawplanet đã có sẵn nên ko cần viết thêm logic xuay --> tịnh tiến ở đây nữa 
		moons[index].drawOrrbit();
		moons[index].drawPlanet();
	}

	// Bọc lại bằng glPush tránh bị xung đột lỗi 
	glPushMatrix();
		// BẮT ĐÀU VẼ HÀNH TINH 
		glRotatef(tiltAngle, 0.0f, 0.0f, 1.0f);
		glRotatef(currentRotationAngle, 0.0f, 1.0f, 0.0f);
		glColor3fv(color);
		glutSolidSphere(radius, 50, 50);
	glPopMatrix();

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

	// Đệ quy cho các moons cũng được cập nhật vòng quay theo TG 
	for (int index = 0; index < moons.size(); index++) {
		moons[index].updateTime();
	}
}
	