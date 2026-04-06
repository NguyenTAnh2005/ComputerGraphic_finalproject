#include "../include/SceneManager.h"
#include "../include/TextureUtils.h"
#include "../include/SkyboxService.h"
#include <GL/glut.h>
#include<iostream>
using namespace std;


// Tạo các hành tinh 
void SceneManager::initPlanets() {
    // --- 1. MẶT TRỜI ---
    GLuint sun_textureID = loadTexture("assets/textures/sun.jpg");
    // Rad: 696,340km, Dist: 0.0 AU, Tilt: 7.25, Day: 648h, Orbit: 1.0 (tránh chia 0)
    RealSpaceData sunData = { "Sun", 696340.0, 0.0, 7.25f, {1.0f, 1.0f, 0.0f}, 648.0, 1.0, false, sun_textureID };
    solarSystem.push_back(Planet::createFromRealData(sunData));
    // --- 2. SAO THỦY (Mercury) ---
    GLuint mercury_textureID = loadTexture("assets/textures/mercury.jpg");
    // Rad: 2,440km, Dist: 0.39 AU, Tilt: 0.03, Day: 1407.6h, Orbit: 88 days
    RealSpaceData merData = { "Mercury", 2439.7, 0.39, 0.03f, {0.7f, 0.7f, 0.7f}, 1407.6, 88.0, false, mercury_textureID };
    solarSystem.push_back(Planet::createFromRealData(merData));

    // --- 3. SAO KIM (Venus) ---
    GLuint venus_textureID = loadTexture("assets/textures/venus.jpg");
    // Rad: 6,051km, Dist: 0.72 AU, Tilt: 177.3, Day: 5832h, Orbit: 224.7 days
    RealSpaceData venusData = { "Venus", 6051.8, 0.72, 177.3f, {0.9f, 0.6f, 0.2f}, 5832.0, 224.7, false, venus_textureID };
    solarSystem.push_back(Planet::createFromRealData(venusData));

    // --- 4. TRÁI ĐẤT (Earth) ---
    GLuint earth_textureID = loadTexture("assets/textures/earth.jpg");
    // Rad: 6371km, Dist: 1.0 AU
    RealSpaceData earthData = { "Earth", 6371.0, 1.0, 23.5f, {0.2f, 0.3f, 1.0f}, 24.0, 365.25, false, earth_textureID };
    Planet earth = Planet::createFromRealData(earthData);
    // MẶT TRĂNG
    GLuint moon_textureID = loadTexture("assets/textures/moon.jpg");
    // Rad: 1737km, Dist: 0.02 AU (Đã scale up để dễ nhìn, nếu thực tế thì cách khá xa)
    RealSpaceData moonData = { "Moon", 1737.0, 0.02, 5.1f, {0.8f, 0.8f, 0.8f}, 655.0, 27.3, false, moon_textureID };
    earth.addMoon(Planet::createFromRealData(moonData));
    solarSystem.push_back(earth);

    // --- 5. SAO HỎA (Mars) ---
    GLuint mars_textureID = loadTexture("assets/textures/mars.jpg");
    // Rad: 3,389km, Dist: 1.52 AU
    RealSpaceData marsData = { "Mars", 3389.5, 1.52, 25.2f, {1.0f, 0.2f, 0.1f}, 24.6, 687.0, false, mars_textureID };
    Planet mars = Planet::createFromRealData(marsData);
    solarSystem.push_back(mars);

    // --- 6. SAO MỘC (Jupiter) ---
    GLuint jupiter_textureID = loadTexture("assets/textures/jupiter.jpg");
    // Rad: 69,911km, Dist: 5.20 AU
    RealSpaceData jupiterData = { "Jupiter", 69911.0, 5.20, 3.1f, {0.8f, 0.6f, 0.4f}, 9.9, 4333.0, false, jupiter_textureID };
    Planet jupiter = Planet::createFromRealData(jupiterData);
    GLuint io_textureID = loadTexture("assets/textures/io.jpg");
    GLuint europa_textureID = loadTexture("assets/textures/europa.jpg");
    jupiter.addMoon(Planet::createFromRealData({ "Io", 1821.0, 0.12, 0.0f, {1.0f, 1.0f, 0.0f}, 42.0, 1.7, false, io_textureID }));
    jupiter.addMoon(Planet::createFromRealData({ "Europa", 1560.0, 0.15, 0.0f, {0.9f, 0.9f, 0.8f}, 85.0, 3.5, false, europa_textureID }));
    solarSystem.push_back(jupiter);

    // --- 7. SAO THỔ (Saturn) ---
    GLuint saturn_textureID = loadTexture("assets/textures/saturn.jpg");
    // Rad: 58,232km, Dist: 9.58 AU
    RealSpaceData saturnData = { "Saturn", 58232.0, 9.58, 26.7f, {0.9f, 0.8f, 0.5f}, 10.7, 10759.0 , true, saturn_textureID };
    Planet saturn = Planet::createFromRealData(saturnData);

    GLuint titan_textureID = loadTexture("assets/textures/titan.jpg");
    saturn.addMoon(Planet::createFromRealData({ "Titan", 2574.0, 0.18, 0.0f, {0.9f, 0.7f, 0.1f}, 382.0, 15.9, false, titan_textureID }));
    solarSystem.push_back(saturn);

    // --- 8. SAO THIÊN VƯƠNG (Uranus) ---
    GLuint uranus_textureID = loadTexture("assets/textures/uranus.jpg");
    // Rad: 25,362km, Dist: 19.22 AU
    RealSpaceData uranusData = { "Uranus", 25362.0, 19.22, 97.8f, {0.6f, 0.8f, 0.9f}, 17.2, 30687.0, true, uranus_textureID };
    solarSystem.push_back(Planet::createFromRealData(uranusData));

    // --- 9. SAO HẢI VƯƠNG (Neptune) ---
    GLuint neptune_textureID = loadTexture("assets/textures/neptune.jpg");
    // Rad: 24,622km, Dist: 30.05 AU
    RealSpaceData neptuneData = { "Neptune", 24622.0, 30.05, 28.3f, {0.2f, 0.4f, 0.9f}, 16.1, 60190.0, false, neptune_textureID };
    solarSystem.push_back(Planet::createFromRealData(neptuneData));
}

// In thông tin lên Console
void SceneManager::printDashBoard() {
    system("cls");
    // IN HDSD CỨNG
    cout << "====================================================\n";
    cout << "      MO PHONG HE MAT TROI 3D - HUONG DAN SU DUNG   \n";
    cout << "====================================================\n";
    cout << "[DIEU KHIEN CAMERA]\n";
    cout << "Phong to - [ W ]  hoac lan chuot len.\n";
    cout << "Thu nho - [ S ] hoac lan chuot xuong.\n";
    cout << "Thu nho - [ S ] hoac lan chuot xuong.\n";
    cout << "Xuay camera doc - [ Mui ten len / xuong ] hoac nhan giu nut trai chuot + di chuyen\n";
    cout << "Xuay camera ngang - [ Mui ten trai / phai ] hoac nhan giu nut trai chuot + di chuyen\n";
    cout << "                      ";
    cout << "[THEO DOI HANH TINH - MAT TRANG]\n";
    cout << "*** HANH TINH: \n";
    cout << "[1] - Mat troi (The Sun)\n";
    cout << "[2] - Sao Thuy (The Mercury)\n";
    cout << "[3] - Sao Kim (The Venus)\n";
    cout << "[4] - Trai Dat (The Earth)\n";
    cout << "[5] - Sao Hoa (The Mars)\n";
    cout << "[6] - Sao Moc (The Jupiter)\n";
    cout << "[7] - Sao Tho (The Sarturn)\n";
    cout << "[8] - Sao Thien Vuong (The Uranus)\n";
    cout << "[9] - Sao Hai Vuong (The Neptune)\n";
    cout << "*** MAT TRANG: \n";
    cout << "[M] - The Moon (Earth)\n";
    cout << "[I] - The Io (Jupiter)\n";
    cout << "[M] - The Europa (Jupiter)\n";
    cout << "[M] - The Titan (Saturn)\n";
    cout << "====================================================\n\n";

    if (currentPLanetIndex >= 0 && currentPLanetIndex < solarSystem.size()) {
        if (currentMoonIndex != -1) {
            // Đang focus mặt trăng
            solarSystem[currentPLanetIndex].getMoons()[currentMoonIndex].printInfo(true);
        }
        else {
            // Đang focus hành tinh mẹ
            solarSystem[currentPLanetIndex].printInfo(false);
        }
    }
}

// Cập nhật khung hình
void SceneManager::updateTime() {
    if (isPaused == false) {
        for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
            solarSystem[planetIndex].updateTime();
        }
    }
}

// Tính toán vị trí mới của camera dựa theo hành tinh tele
void SceneManager::getCameraTarget(float& targetX, float& targetY, float& targetZ) {
    // Khởi tạo vị trí target rỗng hiện tại
    
    if (currentPLanetIndex >= 0 && currentPLanetIndex < solarSystem.size()) {
        // Lấy vị trí của hành tinh mẹ
        solarSystem[currentPLanetIndex].getPosition(targetX, targetY, targetZ);

        if (currentMoonIndex != -1) {
            Planet& parent = solarSystem[currentPLanetIndex];
            Planet& moon = parent.getMoons()[currentMoonIndex];

            // Lấy vị trí local của mặt trăng (chưa bị ảnh hưởng bởi hành tinh mẹ)
            float moonLocalX = 0.0f, moonLocalY = 0.0f, moonLocalZ = 0.0f;
            moon.getPosition(moonLocalX, moonLocalY, moonLocalZ);

            // Tính toán độ nghiêng (Tilt) của hành tinh mẹ áp lên mặt trăng (Xoay quanh trục Z cục bộ)
            float parentTiltRad = parent.getTiltAngle();
            float moonTiltedX = moonLocalX * cos(parentTiltRad);
            float moonTiltedY = moonLocalX * sin(parentTiltRad);
            float moonTiltedZ = moonLocalZ; // Quay quanh trục Z nên Z giữ nguyên

            // Xoay theo quỹ đạo của hành tinh mẹ (Orbit Rotation - Xoay quanh trục Y)
            // Lợi dụng targetX và targetZ hiện tại của mẹ để tìm góc xoay cos(orbit) và sin(orbit)
            float parentDist = parent.getDistance();
            float pCos = 1.0f, pSin = 0.0f;
            if (parentDist > 0.0f) {
                pCos = targetX / parentDist;  // tương đương cos(currentOrbitAngle)
                pSin = -targetZ / parentDist; // tương đương sin(currentOrbitAngle)
            }

            //Chuyển đổi sang World Space và cộng vào vị trí tuyệt đối của hành tinh mẹ
            float finalMoonX = targetX + (moonTiltedX * pCos + moonTiltedZ * pSin);
            float finalMoonY = targetY + moonTiltedY;
            float finalMoonZ = targetZ + (-moonTiltedX * pSin + moonTiltedZ * pCos);

            // Gán lại tâm nhìn của Camera
            targetX = finalMoonX;
            targetY = finalMoonY;
            targetZ = finalMoonZ;
        }
    }
}

// Tương tác với các phím thường 
void SceneManager::handleKeyboard(unsigned char key, Camera& cam) {
    switch (key) {
    case 'w': case 'W': cam.ZoomIn();  break;
    case 's': case 'S': cam.ZoomOut(); break;
    case ' ': isPaused = !isPaused; break;
    }
    if (key >= '1' && key <= '9') {
        int index = key - '1';
        if (index < solarSystem.size()) {
            // các phím '1' -> '9' có giá trị ascii từ 49 -- 57 việc - '1' sẽ giúp ra giá trị index
            // key = '1' --> ra giá trị 0 --> targetIndex = 0 --> chỉ mặt trời 
            currentPLanetIndex = index;
            currentMoonIndex = -1;
            if (index == 0) { cam.camRadius = 50.0f; }
            else cam.camRadius = 15.0f;
            printDashBoard();
        }
    }
    if (key == 't' || key == 'T') {
        currentPLanetIndex = 6;     // Sao thổ
        currentMoonIndex = 0;       // Titan
        cam.camRadius = 3.0f;
        printDashBoard();
    }
    if (key == 'm' || key == 'M') {
        currentPLanetIndex = 3;     // Trái đất
        currentMoonIndex = 0;       // Moon
        cam.camRadius = 3.0f;
        printDashBoard();
    }
    if (key == 'i' || key == 'I') {
        currentPLanetIndex = 5;     // Sao mộc
        currentMoonIndex = 0;       // Io
        cam.camRadius = 3.0f;
        printDashBoard();
    }
    if (key == 'E' || key == 'e') {
        currentPLanetIndex = 5;     // Sao mộc
        currentMoonIndex = 1;       // Europa
        cam.camRadius = 3.0f;
        printDashBoard();
    }
}

// Vẽ các hành tinh 
void SceneManager::drawAll() {
    // For in SolarSys, drawOrbit + drawPlanet
    for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
        solarSystem[planetIndex].drawOrrbit();
        solarSystem[planetIndex].drawPlanet();
    }
}