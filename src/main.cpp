#include <GL/glut.h>
#include <vector>
#include "../include/Planet.h"
using namespace std;
vector <Planet> solarSystem;
// Các biến thông số điều khiển camera
float camRadius = 50.0f;    // r từ cam --> tâm tọa độ ( mặt trời) 
float camYaw = 0.0f;        // góc xuay Theta ( trái phải ) --- radian
float camPitch = 0.5f;      // góc xuay Phi ( lên xuống ) --- radian
bool isPaused = false;      // Toggle ngưng đọng TG 

// Hành tinh đang điều khiển 
int currentTargetIndex = 0; // Mặt trời


// Các function lắng nghe bàn phím --> điều chỉnh các thông số điều khiển camera
// Function lắng nghe bàn phím thường
void keyboard(unsigned char key, int x, int y) {
    // x,y là tọa độ con chuột lúc bấm phím, hiện tại chưa cần use
    switch (key) {
        case 'w': case 'W':
            camRadius -= 1.5f;
            // Giới hạn độ gần, ko cho gần dưới 5.0f
            if (camRadius < 5.0f) { camRadius = 5.0f;}
            break;
        case 's': case 'S':
            camRadius += 1.5f;
            if (camRadius > 150.0f) { camRadius = 150.0f;}
            break;
        case ' ':
            // Nếu nhấn space thì bật / tắt ngưng đọng TG 
            isPaused = !isPaused;
            break;
    }

    // Bổ sung thêm set targetIndex 
    if (key >= '1' && key <= '9') {
        int index = key - '1' ;
        if (index < solarSystem.size()) {
            // các phím '1' -> '9' có giá trị ascii từ 49 -- 57
            // việc - '1' sẽ giúp ra giá trị index
            // key = '1' --> ra giá trị 0 --> targetIndex = 0 --> chỉ mặt trời 
            currentTargetIndex = index;

            if (index == 0) { camRadius = 50.0f; }
            else camRadius = 15.0f;
        }
    }
    // Báo cho OpenGL thông sô thay đổi ==> Vẽ lại khung hình
    glutPostRedisplay();
}

// Function lắng nghe bàn phím đặc biệt - mũi tên 
void specialKeys(int key, int x, int y) {
    // thông số x, y tương tự như hàm trên
    const float angleSpeed = 0.05f; // Độ quay 1 lần ( Radian )
    switch (key) {
        case GLUT_KEY_LEFT: 
            camYaw -= angleSpeed; 
            break;
        
        case GLUT_KEY_RIGHT:
            camYaw += angleSpeed; 
            break;

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
    glutPostRedisplay();
}

void initPlanets() {
    // --- 1. MẶT TRỜI ---
    // Rad: 696,340km, Dist: 0.0 AU, Tilt: 7.25, Day: 648h, Orbit: 1.0 (tránh chia 0)
    RealSpaceData sunData = { "Sun", 696340.0, 0.0, 7.25f, {1.0f, 1.0f, 0.0f}, 648.0, 1.0, false};
    solarSystem.push_back(Planet::createFromRealData(sunData));

    // --- 2. SAO THỦY (Mercury) ---
    // Rad: 2,440km, Dist: 0.39 AU, Tilt: 0.03, Day: 1407.6h, Orbit: 88 days
    RealSpaceData merData = { "Mercury", 2439.7, 0.39, 0.03f, {0.7f, 0.7f, 0.7f}, 1407.6, 88.0, false};
    solarSystem.push_back(Planet::createFromRealData(merData));

    // --- 3. SAO KIM (Venus) ---
    // Rad: 6,051km, Dist: 0.72 AU, Tilt: 177.3, Day: 5832h, Orbit: 224.7 days
    RealSpaceData venData = { "Venus", 6051.8, 0.72, 177.3f, {0.9f, 0.6f, 0.2f}, 5832.0, 224.7, false };
    solarSystem.push_back(Planet::createFromRealData(venData));

    // --- 4. TRÁI ĐẤT (Earth) ---
    // Rad: 6371km, Dist: 1.0 AU
    RealSpaceData earData = { "Earth", 6371.0, 1.0, 23.5f, {0.2f, 0.3f, 1.0f}, 24.0, 365.25, false};
    Planet earth = Planet::createFromRealData(earData);

    // MẶT TRĂNG
    // Rad: 1737km, Dist: 0.02 AU (Đã scale up để dễ nhìn, nếu thực tế thì cách khá xa)
    RealSpaceData moonData = { "Moon", 1737.0, 0.02, 5.1f, {0.8f, 0.8f, 0.8f}, 655.0, 27.3, false};
    earth.addMoon(Planet::createFromRealData(moonData));
    solarSystem.push_back(earth);

    // --- 5. SAO HỎA (Mars) ---
    // Rad: 3,389km, Dist: 1.52 AU
    RealSpaceData marData = { "Mars", 3389.5, 1.52, 25.2f, {1.0f, 0.2f, 0.1f}, 24.6, 687.0, false};
    Planet mars = Planet::createFromRealData(marData);
    // thực tế Phobo và deimos có kích thước khá nhỏ  11km và 6km 
    // Kích thước được phóng đại hơn để dễ quan sát hơn ( x 20 lần)
    mars.addMoon(Planet::createFromRealData({ "Phobos", 220.0, 0.03, 1.0f, {0.6f, 0.6f, 0.6f}, 7.6, 0.3 , false}));
    mars.addMoon(Planet::createFromRealData({ "Deimos", 120.0, 0.05, 1.0f, {0.5f, 0.5f, 0.5f}, 30.0, 1.2, false }));
    solarSystem.push_back(mars);

    // --- 6. SAO MỘC (Jupiter) ---
    // Rad: 69,911km, Dist: 5.20 AU
    RealSpaceData jupData = { "Jupiter", 69911.0, 5.20, 3.1f, {0.8f, 0.6f, 0.4f}, 9.9, 4333.0, false };
    Planet jupiter = Planet::createFromRealData(jupData);
    // Các mặt trăng Galilean
    jupiter.addMoon(Planet::createFromRealData({ "Io", 1821.0, 0.12, 0.0f, {1.0f, 1.0f, 0.0f}, 42.0, 1.7, false}));
    jupiter.addMoon(Planet::createFromRealData({ "Europa", 1560.0, 0.15, 0.0f, {0.9f, 0.9f, 0.8f}, 85.0, 3.5, false }));
    solarSystem.push_back(jupiter);

    // --- 7. SAO THỔ (Saturn) ---
    // Rad: 58,232km, Dist: 9.58 AU
    RealSpaceData satData = { "Saturn", 58232.0, 9.58, 26.7f, {0.9f, 0.8f, 0.5f}, 10.7, 10759.0 , true};
    Planet saturn = Planet::createFromRealData(satData);
    saturn.addMoon(Planet::createFromRealData({ "Titan", 2574.0, 0.18, 0.0f, {0.9f, 0.7f, 0.1f}, 382.0, 15.9, false }));
    solarSystem.push_back(saturn);

    // --- 8. SAO THIÊN VƯƠNG (Uranus) ---
    // Rad: 25,362km, Dist: 19.22 AU
    RealSpaceData uraData = { "Uranus", 25362.0, 19.22, 97.8f, {0.6f, 0.8f, 0.9f}, 17.2, 30687.0, true };
    solarSystem.push_back(Planet::createFromRealData(uraData));

    // --- 9. SAO HẢI VƯƠNG (Neptune) ---
    // Rad: 24,622km, Dist: 30.05 AU
    RealSpaceData nepData = { "Neptune", 24622.0, 30.05, 28.3f, {0.2f, 0.4f, 0.9f}, 16.1, 60190.0, false};
    solarSystem.push_back(Planet::createFromRealData(nepData));
}
void display() {
    // Clear display and Bộ nhớ độ sâu
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Khởi tạo vị trí target rỗng hiện tại
    float targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
    if (currentTargetIndex >= 0 && currentTargetIndex < solarSystem.size()) {
        solarSystem[currentTargetIndex].getPosition(targetX, targetY, targetZ);
    }
    //Tính toán vị trí Mắt Camera
    // Thay vì tính từ gốc 0,0,0, ta cộng thêm targetX, targetY, targetZ vào
    // => Sợi dây Camera lúc này được cột vào hành tinh mục tiêu!
    float camX = targetX + camRadius * cos(camPitch) * sin(camYaw);
    float camY = targetY + camRadius * sin(camPitch);
    float camZ = targetZ + camRadius * cos(camPitch) * cos(camYaw);

    // Set Camera
    gluLookAt(camX, camY, camZ,   // Mắt camera đang nằm ở X, Y, Z vừa tính
        targetX, targetY, targetZ,   // Nhìn thẳng vào vị trí hành tinh (x, y, z)
        0.0f, 1.0f, 0.0f);  // Quy định trục Y là hướng lên trời

    // For in SolarSys, drawOrbit + drawPlanet
    for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
        solarSystem[planetIndex].drawOrrbit();
        solarSystem[planetIndex].drawPlanet();
    }

    // Đẩy hình ảnh từ bộ nhớ ra display 
    glutSwapBuffers();
}


void timer(int value) {
    // Nếu ko pause thì mới cho xuay ( cộng góc + vẽ lại ) 
    if (isPaused == false) {
        for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
            solarSystem[planetIndex].updateTime();
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Solar System by Gemini Pro");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    initPlanets();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    // ĐĂNG KÝ HÀM BÀN PHÍM VỚI OPEN GL
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1200.0 / 800.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();

    return 0;
}