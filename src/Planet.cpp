#include "../include/Planet.h"
#define PI 3.14159265358979323846
#include <iostream>
using namespace std;

// Định nghĩa các chuẩn 
const float EARTH_RAD_KM = 6371.0f;		// bán kính km của trái đất
const float EARTH_DIST_AU = 0.5f;		// D từ trái đất đến mặt trời = 1 đơn vị thiên văn ~ 150M km -- set là 1.0f nhưng khá gần nên chỉnh lại
// Chu kỳ tự quay của Trái đất = 24h  -- Rotation Speed
//const float EARTH_DAY_HOURS = 24.0f;
const float EARTH_DAY_HOURS = 2.40f;
// Chu kỳ quay quanh mặt trời = 365 ngày 6 hours -- OrbitSpeed
//const float EARTH_YEARS_DAY = 365.25f;	 
const float EARTH_YEAR_DAYS = 36.525f;

// Các chuẩn 1 được chuẩn hóa tại Open GL 
const float EARTH_RAD_GL = 0.4f;		// Trái đất to 0.4
const float EARTH_DIST_GL = 6.0f;		// Trái đất cách mặt trời 0.6
const float EARTH_ROT_SPEED_GL = 1.0f;	// Trái đất tự quay với tốc độ = 1
const float EARTH_ORB_SPEED_GL = 0.7f;	// Trái đất bay với tốc độ 0.7 đơn vị góc / frame


// Constructor
Planet::Planet(string na, float rad, float dist, float tilt, float rCol, float gCol, float bCol, float orbSpeed, float rotSpeed, bool ring, GLuint textureid) {
	name = na;
	radius = rad;
	distance = dist;
	tiltAngle = tilt;
	color[0] = rCol;
	color[1] = gCol;
	color[2] = bCol;
	orbitSpeed = orbSpeed;
	rotationSpeed = rotSpeed;
	hasRing = ring;
	textureID = textureid;
	// TRẠNG THÁI MẶC ĐỊNH: Bất kể hành tinh nào vừa đẻ ra, góc quay luôn xuất phát từ 0 độ
	currentOrbitAngle = 0.0f;
	currentRotationAngle = 0.0f;
}

// Hàm biến đổi từ giá trị thực ở Struct sang OBJect với GT chuẩn hóa 
Planet Planet::createFromRealData(RealSpaceData data) {
	//Tính toán chuẩn hóa 
	float resDist = (data.distAU == 0) ? 0.0f : sqrt(data.distAU / EARTH_DIST_AU) * EARTH_DIST_GL;
	// Nếu dùng CT của Wiki thì tỉ lệ lệch khá nhiều, không đủ vẽ
	// --> Clamp 1.5 là sun max, 1.1 cho sao mộc (nhỏ hơn mỗi mặt trời)
	// Tạo ra sự phân cấp và đảm bảo các hành tinh ko quá nhỏ
	float resRad = (data.radiusKM / EARTH_RAD_KM) * EARTH_RAD_GL;
	if (data.name == "Sun") {resRad = 3.0f;}
	else if (resRad > 3.0f) { resRad = 1.9f; }

	float resOrbSpeed = (data.distAU == 0) ? 0.0f : (EARTH_YEAR_DAYS/data.yearDays) * EARTH_ORB_SPEED_GL;

	float resRotSpeed = (EARTH_DAY_HOURS / data.dayHours) * EARTH_ROT_SPEED_GL;

	return Planet(data.name, resRad, resDist, data.tilt,
				  data.color[0], data.color[1], data.color[2],
				  resOrbSpeed,resRotSpeed, data.hasRing, data.textureID);
}

void Planet::drawOrrbit() {
	//Check: Không phải Mặt Trời thì mới vẽ.
	//Save : Lưu trạng thái cũ.
	//Color : Lấy bút màu xám.
	//Loop : Chạy 360 vòng, mỗi vòng tính 1 tọa độ mới rồi chấm 1 điểm.
	//Connect : OpenGL tự nối các điểm thành vòng tròn.
	//Load : Trả lại trạng thái sạch sẽ.
	glDisable(GL_LIGHTING);
	if (distance <= 0.0f) {
		glEnable(GL_LIGHTING);
		return;
	}
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
	glEnable(GL_LIGHTING);
}

void Planet::drawMoons() {
	for (int index = 0; index < moons.size(); index++) {
		moons[index].drawOrrbit();
		moons[index].drawPlanet();
	}
}

void Planet::drawRing() {
	glPushMatrix();

	// TẤT CẢ VÀNH ĐAI ĐỀU PHẢI NẰM LÊN XÍCH ĐẠO (Xoay 90 độ quanh trục X)
	// Lệnh nghiêng tiltAngle ở trên sẽ lo phần bẻ góc thực tế cho từng hành tinh
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	GLUquadric* quadric = gluNewQuadric();
	if (name == "Saturn") {
		GLfloat ring_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat ring_diffuse[] = { color[0], color[1], color[2], 1.0f };
		GLfloat ring_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat ring_shininess = 50.0f;
		//glColor3f(0.8f, 0.7f, 0.6f); // Màu xám vàng
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ring_emission);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ring_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ring_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ring_shininess);

		GLfloat ring_ambient[] = { color[0] , color[1] , color[2] , 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ring_ambient);

		gluDisk(quadric, radius * 1.25f, radius * 1.8f, 50, 1);
	}
	else if (name == "Uranus") {
		glColor3f(0.5f, 0.8f, 0.8f); // Màu xanh lơ nhạt, vành đai mỏng hơn
		GLfloat ring_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat ring_diffuse[] = { color[0], color[1], color[2], 1.0f };
		GLfloat ring_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat ring_shininess = 50.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ring_emission);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ring_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ring_specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ring_shininess);

		GLfloat ring_ambient[] = { color[0] , color[1] , color[2] , 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ring_ambient);

		gluDisk(quadric, radius * 1.25f, radius * 1.4f, 50, 1);
	}
	gluDeleteQuadric(quadric);

	glPopMatrix();
}

void Planet::setupMaterial() {
	if (name == "sun" || name == "Sun") {
		// Mặt Trời tự phát ra ánh sáng màu vàng rực
		GLfloat sun_emission[] = { color[0], color[1], color[2], 1.0f };
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);

		// Tắt Diffuse và Specular cho mặt trời ==> Sáng tỏa xung quanh 
		GLfloat black_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, black_color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, black_color);

	}
	else {
		// Tắt tự phát sáng
		GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);

		// Cấp màu sắc gốc - Diffuse
		GLfloat planet_diffuse[] = { color[0], color[1], color[2], 1.0f };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, planet_diffuse);

		// Cấp độ bóng (Specular & Shininess
		GLfloat planet_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat planet_shininess = 50.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, planet_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, planet_shininess);
	}
}

void Planet::drawPlanet() {
	// Lưu vị trí mặt trời 
	glPushMatrix();
		// Xuay hành tinh quanh trục Y rồi đưa ra quỹ đạo
		glRotatef(currentOrbitAngle, 0.0f, 1.0f, 0.0f);
		glTranslatef(distance, 0.0f, 0.0f);
		// Bọc lại bằng glPush tránh bị xung đột lỗi 
		glPushMatrix();

			// Nghiêng trục cho cả hành tinh và vành đai 
			glRotatef(tiltAngle, 0.0f, 0.0f, 1.0f);
			// Vẽ vành đai
			if (hasRing) { drawRing(); }
			// Cấu hình lightning cho mặt trời và các hành tinh khác
			setupMaterial();
			// BẮT ĐÀU VẼ HÀNH TINH 
			glRotatef(currentRotationAngle, 0.0f, 1.0f, 0.0f);
			glEnable(GL_TEXTURE_2D);								// Cho phép dán ảnh
			glBindTexture(GL_TEXTURE_2D, textureID);				// Chọn ảnh của hành tinh này
			GLUquadric* quadric = gluNewQuadric();
			gluQuadricTexture(quadric, GL_TRUE);					// Tự động tính tọa độ dán ảnh (UV Mapping)
			gluQuadricNormals(quadric, GLU_SMOOTH);					// Giúp ánh sáng mịn màng hơn
			// Vẽ khối cầu bằng GLU thay vì GLUT
			glPushMatrix();
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			if (name == "Sun") { gluSphere(quadric, radius, 100, 100); }
			else { gluSphere(quadric, radius, 50, 50); }
			glPopMatrix();
			gluDeleteQuadric(quadric);						// Vẽ xong thì dọn dẹp bộ nhớ
			glDisable(GL_TEXTURE_2D);						// Tắt công tắc để không ảnh hưởng vật thể khác
		glPopMatrix();
	// Trả về vị trí gốc tọa độ
	glPopMatrix();
}

void Planet::updateTime() {
	// Cập nhật góc của hành tinh
	currentOrbitAngle += orbitSpeed;
	if (currentOrbitAngle >= 360.0f) currentOrbitAngle -= 360.0f;

	// Cập nhật góc tự xuay của hành tinh
	currentRotationAngle += rotationSpeed;
	if (currentRotationAngle >= 360.0f) currentRotationAngle -= 360.0f;

	// Đệ quy cho các moons cũng được cập nhật vòng quay theo TG 
	for (int index = 0; index < moons.size(); index++) {
		moons[index].updateTime();
	}
}

void Planet::getPosition(float &x, float &y, float &z) {
	float currentOrbitAngleRad = currentOrbitAngle * PI / 180.0f;
	x = distance * cos(currentOrbitAngleRad);
	y = 0;
	z = -1 * distance * sin(currentOrbitAngleRad);
}

vector<Planet>& Planet::getMoons() {
	return moons;
}
float Planet::getTiltAngle() {
	return (tiltAngle*PI)/180.0f;
}
float Planet::getDistance() {
	return distance;
}
void Planet::printInfo(bool isMoon) {
	float real_radius = (radius * EARTH_RAD_KM)/EARTH_RAD_GL;
	float real_distance = (pow(distance, 2)/ pow(EARTH_DIST_GL, 2)) * EARTH_DIST_AU;
	float real_yearDays = 0.0f;
	if (orbitSpeed > 0) {
		real_yearDays = (EARTH_YEAR_DAYS * EARTH_ORB_SPEED_GL) / orbitSpeed;
	}
	float real_dayHours = (EARTH_DAY_HOURS * EARTH_ROT_SPEED_GL) / rotationSpeed;

	string type = isMoon ? "VE TINH ( MAT TRANG) " : "HANH TINH";
	cout << "------------------------------------------" << endl;
	cout << "MUC TIEU DANG QUAN SAT " << name << " \n";
	cout << " Phan loai: " << type << " \n";
	cout << " Ban kinh : " << real_radius << " km \n";
	cout << " Khoang cach den vat chu: " << real_distance << " Au - ( don vi thien van) \n";
	cout << " Chu ky tu quay: " << real_dayHours << " (gio) \n";
	if (name == "Sun" || name == "sun") {
		cout << "Chu ky quy dao: N/A (Tam he mat troi)" << endl;
	}
	else {
		cout << "Chu ky quy dao: " << real_yearDays << " ngay" << endl;
	}
	cout << "------------------------------------------" << endl;
}

	