#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include<iostream>
#include <GL/glut.h>
#include <vector>
#include "../include/Planet.h"
using namespace std;
vector <Planet> solarSystem;
GLuint skyBoxTextures[6];
float minCamradius = 1.5f;
float maxCamradius = 150.0f;

// FUNCTION - Đọc ảnh, nạp ảnh lên GPU, cấp id --> Khi dán ảnh cho hành tinh chỉ cần gọi ID
// Code nâng cao - Copy chat 
GLuint loadTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 4) format = GL_RGBA;
        //glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);

        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
        cout << "[SUCCESS] Loaded: " << filename << " (" << width << "x" << height << ")" << endl;
    }
    else {
        cout << "[ERROR] Failed to load texture: " << filename << endl;
    }
    stbi_image_free(data);
    return textureID;
}



// Function lấy 6 mặt của Skybox
void initSkybox() {
    skyBoxTextures[0] = loadTexture("assets/textures/right.png");
    skyBoxTextures[1] = loadTexture("assets/textures/left.png");
    skyBoxTextures[2] = loadTexture("assets/textures/top.png");
    skyBoxTextures[3] = loadTexture("assets/textures/bot.png");
    skyBoxTextures[4] = loadTexture("assets/textures/front.png");
    skyBoxTextures[5] = loadTexture("assets/textures/back.png");
}

struct Vec3i {
    int x, y, z;
};
// Function ghép ảnh vào hệ trục tạo hình lập phương
void graftFace(float r, GLuint texture, Vec3i LB, Vec3i RB, Vec3i TR, Vec3i TL) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    // Góc trái dưới 
    glTexCoord2f(0, 0);
    glVertex3f(LB.x * r, LB.y * r, LB.z * r);

    // Góc phải dưới 
    glTexCoord2f(1, 0);
    glVertex3f(RB.x * r, RB.y * r, RB.z * r);

    // Góc phải trên
    glTexCoord2f(1, 1);
    glVertex3f(TR.x * r, TR.y * r, TR.z * r);

    // Góc trái trên (Đã sửa lại thành 0, 1)
    glTexCoord2f(0, 1);
    glVertex3f(TL.x * r, TL.y * r, TL.z * r);

    glEnd();
}

// Function vẽ Sky Box 
void drawSkybox(float camX, float camY, float camZ) {
    // Tắt ánh sáng để bầu trời không bị tối đi do nguồn sáng Mặt Trời
    glDisable(GL_LIGHTING);
    // Tắt ghi độ sâu để bầu trời luôn luôn nằm ở lớp nền xa nhất
    glDepthMask(GL_FALSE);
    glEnable(GL_TEXTURE_2D);
    // Kích thước sky box 
    float size = 300.f; 
    glPushMatrix();
    // Đảm bảo khi cam đến đâu thì tâm ngân hà luôn ở đó, tránh TH đi ra khỏi Sky box
    glTranslatef(camX, camY, camZ);

    // Ghép các mặt ảnh vào tạo hình lập phương
    // Mặt phải (Right) - Trục X dương
    float m = size / 2.0;
    // Mặt phải (Right) - Trục X dương
    graftFace(m, skyBoxTextures[0], { 1, -1, 1 }, { 1, -1, -1 }, { 1, 1, -1 }, { 1, 1, 1 });

    // Mặt trái (Left) - Trục X âm
    graftFace(m, skyBoxTextures[1], { -1, -1, -1 }, { -1, -1, 1 }, { -1, 1, 1 }, { -1, 1, -1 });

    // Mặt trên (Top) - Trục Y dương
    graftFace(m, skyBoxTextures[2], { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, 1, -1 });

    // Mặt dưới (Bottom) - Trục Y âm
    graftFace(m, skyBoxTextures[3], { -1, -1, -1 }, { 1, -1, -1 }, { 1, -1, 1 }, { -1, -1, 1 });

    // Mặt trước (Front) - Trục Z dương
    graftFace(m, skyBoxTextures[4], { -1, -1, 1 }, { 1, -1, 1 }, { 1, 1, 1 }, { -1, 1, 1 });

    // Mặt sau (Back) - Trục Z âm
    graftFace(m, skyBoxTextures[5], { 1, -1, -1 }, { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 });
    
    glPopMatrix();
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
}


// Các biến thông số điều khiển camera
float camRadius = 80.0f;    // r từ cam --> tâm tọa độ ( mặt trời) 
float camYaw = 0.0f;        // góc xuay Theta ( trái phải ) --- radian
float camPitch = 0.5f;      // góc xuay Phi ( lên xuống ) --- radian
bool isPaused = false;      // Toggle ngưng đọng TG 
bool isDragging = false;    // Đang nhấn chuột điều khiển ?
int lastMouseX, lastMouseY; // Vị trí cuối cùng của tọa dộ x, y của con trỏ chuột

// Hành tinh đang điều khiển 
int currentPLanetIndex = 0; // Mặt trời 
int currentMoonIndex = -1;  // Mặt trăng của hành tinh đang quan sát, nếu -1 thì là hành tinh mẹ 

// Function hiện thông tin trong console 
void printDashBoard() {
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
// Các function lắng nghe bàn phím --> điều chỉnh các thông số điều khiển camera
// Function lắng nghe bàn phím thường
void keyboard(unsigned char key, int x, int y) {
    // x,y là tọa độ con chuột lúc bấm phím, hiện tại chưa cần use
    switch (key) {
        case 'w': case 'W':
            camRadius -= 1.5f;
            // Giới hạn độ gần, ko cho gần dưới 5.0f
            if (camRadius < minCamradius) { camRadius = minCamradius;}
            break;
        case 's': case 'S':
            camRadius += 1.5f;
            if (camRadius > maxCamradius) { camRadius = maxCamradius;}
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
            currentPLanetIndex = index;
            currentMoonIndex = -1;

            if (index == 0) { camRadius = 50.0f; }
            else camRadius = 15.0f;

            printDashBoard();
        }
    }
    if (key == 't' || key == 'T') {
        currentPLanetIndex = 6;     // Sao thổ
        currentMoonIndex = 0;       // Titan
        camRadius = 3.0f;
        printDashBoard();
    }
    if (key == 'm' || key == 'M') {
        currentPLanetIndex = 3;     // Trái đất
        currentMoonIndex = 0;       // Moon
        camRadius = 3.0f;
        printDashBoard();
    }
    if (key == 'i' || key == 'I') {
        currentPLanetIndex = 5;     // Sao mộc
        currentMoonIndex = 0;       // Io
        camRadius = 3.0f;
        printDashBoard();
    }
    if (key == 'E' || key == 'e') {
        currentPLanetIndex = 5;     // Sao mộc
        currentMoonIndex = 1;       // Europa
        camRadius = 3.0f;
        printDashBoard();
    }
    glutPostRedisplay();
}


// Function lắng nghe sự kiện lăn chuột ( giảm - thu phóng), cũng như nhấn chuột 
// Các button tương ứng trên chuột được quy ước theo số sẵn và theo state 
void mouseControl(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == 3) {
            camRadius -= 2.0f;
            if (camRadius <= minCamradius) camRadius = minCamradius;
        }
        else if (button == 4) {
            camRadius += 2.0f;
            if (camRadius >= maxCamradius) camRadius = maxCamradius;

        }
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
    glutPostRedisplay();
}


void mouseMotion(int x, int y) {
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

        glutPostRedisplay();
    }
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


// Function tạo các hành tinh và lưu vào mảng Solar Systems
void initPlanets() {
    // --- 1. MẶT TRỜI ---
    GLuint sun_textureID = loadTexture("assets/textures/sun.jpg");
    // Rad: 696,340km, Dist: 0.0 AU, Tilt: 7.25, Day: 648h, Orbit: 1.0 (tránh chia 0)
    RealSpaceData sunData = { "Sun", 696340.0, 0.0, 7.25f, {1.0f, 1.0f, 0.0f}, 648.0, 1.0, false, sun_textureID};
    solarSystem.push_back(Planet::createFromRealData(sunData));
    // --- 2. SAO THỦY (Mercury) ---
     GLuint mercury_textureID = loadTexture("assets/textures/mercury.jpg");
    // Rad: 2,440km, Dist: 0.39 AU, Tilt: 0.03, Day: 1407.6h, Orbit: 88 days
    RealSpaceData merData = { "Mercury", 2439.7, 0.39, 0.03f, {0.7f, 0.7f, 0.7f}, 1407.6, 88.0, false, mercury_textureID};
    solarSystem.push_back(Planet::createFromRealData(merData));

    // --- 3. SAO KIM (Venus) ---
    GLuint venus_textureID = loadTexture("assets/textures/venus.jpg");
    // Rad: 6,051km, Dist: 0.72 AU, Tilt: 177.3, Day: 5832h, Orbit: 224.7 days
    RealSpaceData venusData = { "Venus", 6051.8, 0.72, 177.3f, {0.9f, 0.6f, 0.2f}, 5832.0, 224.7, false, venus_textureID};
    solarSystem.push_back(Planet::createFromRealData(venusData));

    // --- 4. TRÁI ĐẤT (Earth) ---
    GLuint earth_textureID = loadTexture("assets/textures/earth.jpg");
    // Rad: 6371km, Dist: 1.0 AU
    RealSpaceData earthData = { "Earth", 6371.0, 1.0, 23.5f, {0.2f, 0.3f, 1.0f}, 24.0, 365.25, false, earth_textureID};
    Planet earth = Planet::createFromRealData(earthData);
    // MẶT TRĂNG
     GLuint moon_textureID = loadTexture("assets/textures/moon.jpg");
    // Rad: 1737km, Dist: 0.02 AU (Đã scale up để dễ nhìn, nếu thực tế thì cách khá xa)
    RealSpaceData moonData = { "Moon", 1737.0, 0.02, 5.1f, {0.8f, 0.8f, 0.8f}, 655.0, 27.3, false, moon_textureID};
    earth.addMoon(Planet::createFromRealData(moonData));
    solarSystem.push_back(earth);

    // --- 5. SAO HỎA (Mars) ---
    GLuint mars_textureID = loadTexture("assets/textures/mars.jpg");
    // Rad: 3,389km, Dist: 1.52 AU
    RealSpaceData marsData = { "Mars", 3389.5, 1.52, 25.2f, {1.0f, 0.2f, 0.1f}, 24.6, 687.0, false, mars_textureID};
    Planet mars = Planet::createFromRealData(marsData);
    solarSystem.push_back(mars);

    // --- 6. SAO MỘC (Jupiter) ---
     GLuint jupiter_textureID = loadTexture("assets/textures/jupiter.jpg");
    // Rad: 69,911km, Dist: 5.20 AU
    RealSpaceData jupiterData = { "Jupiter", 69911.0, 5.20, 3.1f, {0.8f, 0.6f, 0.4f}, 9.9, 4333.0, false, jupiter_textureID};
    Planet jupiter = Planet::createFromRealData(jupiterData);
    GLuint io_textureID = loadTexture("assets/textures/io.jpg");
    GLuint europa_textureID = loadTexture("assets/textures/europa.jpg");
    jupiter.addMoon(Planet::createFromRealData({ "Io", 1821.0, 0.12, 0.0f, {1.0f, 1.0f, 0.0f}, 42.0, 1.7, false, io_textureID }));
    jupiter.addMoon(Planet::createFromRealData({ "Europa", 1560.0, 0.15, 0.0f, {0.9f, 0.9f, 0.8f}, 85.0, 3.5, false, europa_textureID }));
    solarSystem.push_back(jupiter);

    // --- 7. SAO THỔ (Saturn) ---
    GLuint saturn_textureID = loadTexture("assets/textures/saturn.jpg");
    // Rad: 58,232km, Dist: 9.58 AU
    RealSpaceData saturnData = { "Saturn", 58232.0, 9.58, 26.7f, {0.9f, 0.8f, 0.5f}, 10.7, 10759.0 , true, saturn_textureID};
    Planet saturn = Planet::createFromRealData(saturnData);

    GLuint titan_textureID = loadTexture("assets/textures/titan.jpg");
    saturn.addMoon(Planet::createFromRealData({ "Titan", 2574.0, 0.18, 0.0f, {0.9f, 0.7f, 0.1f}, 382.0, 15.9, false, titan_textureID }));
    solarSystem.push_back(saturn);

    // --- 8. SAO THIÊN VƯƠNG (Uranus) ---
    GLuint uranus_textureID = loadTexture("assets/textures/uranus.jpg");
    // Rad: 25,362km, Dist: 19.22 AU
    RealSpaceData uranusData = { "Uranus", 25362.0, 19.22, 97.8f, {0.6f, 0.8f, 0.9f}, 17.2, 30687.0, true, uranus_textureID};
    solarSystem.push_back(Planet::createFromRealData(uranusData));

    // --- 9. SAO HẢI VƯƠNG (Neptune) ---
     GLuint neptune_textureID = loadTexture("assets/textures/neptune.jpg");
    // Rad: 24,622km, Dist: 30.05 AU
    RealSpaceData neptuneData = { "Neptune", 24622.0, 30.05, 28.3f, {0.2f, 0.4f, 0.9f}, 16.1, 60190.0, false, neptune_textureID};
    solarSystem.push_back(Planet::createFromRealData(neptuneData));

}

 
// Function tính toán vị trí camera
void display() {
    // Clear display and Bộ nhớ độ sâu
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Khởi tạo vị trí target rỗng hiện tại
    // Khởi tạo vị trí target rỗng hiện tại
    float targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
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

    drawSkybox(camX, camY, camZ);

    GLfloat light_pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);




    // For in SolarSys, drawOrbit + drawPlanet
    for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
        solarSystem[planetIndex].drawOrrbit();
        solarSystem[planetIndex].drawPlanet();
    }

    // Đẩy hình ảnh từ bộ nhớ ra display 
    glutSwapBuffers();
}


// Function cập nhật khung hình
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


// Function - Tạo cầu dao bật ánh sáng tỏa ra tại mặt trời 
void initLighting() {
    // Enable cấu dao và lắp bóng 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Tạo ánh sáng cho mặt trời ( AS trắng ) 
    // Các mảng 4 số này là (R, G, B, Alpha - độ trong suốt) từ 0 - 1 tương ứng như 0 - 255 
    // ít ai dùng Alpha nhưng hàm của OpenGL thì buộc phải có nên mặc định là 1.0f
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Hắt sáng nhẹ để phần khuất không bị đen kịt
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Tia sáng trắng chiếu trực tiếp
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Tia sáng gây chói cũng màu trắng
    
    // Vị trí nguồn sáng
    //GLfloat light_pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    // gàn vào nguồn sáng
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    //glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}





//Main Function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Solar System by Nguyen Tuan's Anh");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    initLighting();
    initPlanets();
    initSkybox();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    // ĐĂNG KÝ HÀM BÀN PHÍM VỚI OPEN GL
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // Đăng ký hàm xử lý với chuột 
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1200.0 / 800.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();

    return 0;
}