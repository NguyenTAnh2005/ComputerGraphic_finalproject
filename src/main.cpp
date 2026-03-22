#include <GL/glut.h>
#include <vector>
#include "../include/Planet.h"
using namespace std;
vector <Planet> solarSystem;

void initPlanets() {
    // --- 1. MẶT TRỜI ---
    // Rad: 696,340km, Dist: 0.0 AU, Tilt: 7.25, Day: 648h, Orbit: 1.0 (tránh chia 0)
    RealSpaceData sunData = { "Sun", 696340.0, 0.0, 7.25f, {1.0f, 1.0f, 0.0f}, 648.0, 1.0 };
    solarSystem.push_back(Planet::createFromRealData(sunData));

    // --- 2. SAO THỦY (Mercury) ---
    // Rad: 2,440km, Dist: 0.39 AU, Tilt: 0.03, Day: 1407.6h, Orbit: 88 days
    RealSpaceData merData = { "Mercury", 2439.7, 0.39, 0.03f, {0.7f, 0.7f, 0.7f}, 1407.6, 88.0 };
    solarSystem.push_back(Planet::createFromRealData(merData));

    // --- 3. SAO KIM (Venus) ---
    // Rad: 6,051km, Dist: 0.72 AU, Tilt: 177.3, Day: 5832h, Orbit: 224.7 days
    RealSpaceData venData = { "Venus", 6051.8, 0.72, 177.3f, {0.9f, 0.6f, 0.2f}, 5832.0, 224.7 };
    solarSystem.push_back(Planet::createFromRealData(venData));

    // --- 4. TRÁI ĐẤT (Earth) ---
    // Rad: 6371km, Dist: 1.0 AU
    RealSpaceData earData = { "Earth", 6371.0, 1.0, 23.5f, {0.2f, 0.3f, 1.0f}, 24.0, 365.25 };
    Planet earth = Planet::createFromRealData(earData);

    // MẶT TRĂNG
    // Rad: 1737km, Dist: 0.05 AU (Đã scale up để dễ nhìn)
    RealSpaceData moonData = { "Moon", 1737.0, 0.02, 5.1f, {0.8f, 0.8f, 0.8f}, 655.0, 27.3 };
    earth.addMoon(Planet::createFromRealData(moonData));
    solarSystem.push_back(earth);

    // --- 5. SAO HỎA (Mars) ---
    // Rad: 3,389km, Dist: 1.52 AU
    RealSpaceData marData = { "Mars", 3389.5, 1.52, 25.2f, {1.0f, 0.2f, 0.1f}, 24.6, 687.0 };
    Planet mars = Planet::createFromRealData(marData);
    mars.addMoon(Planet::createFromRealData({ "Phobos", 11.0, 0.03, 1.0f, {0.6f, 0.6f, 0.6f}, 7.6, 0.3 }));
    mars.addMoon(Planet::createFromRealData({ "Deimos", 6.0, 0.06, 1.0f, {0.5f, 0.5f, 0.5f}, 30.0, 1.2 }));
    solarSystem.push_back(mars);

    // --- 6. SAO MỘC (Jupiter) ---
    // Rad: 69,911km, Dist: 5.20 AU
    RealSpaceData jupData = { "Jupiter", 69911.0, 5.20, 3.1f, {0.8f, 0.6f, 0.4f}, 9.9, 4333.0 };
    Planet jupiter = Planet::createFromRealData(jupData);
    // Các mặt trăng Galilean
    jupiter.addMoon(Planet::createFromRealData({ "Io", 1821.0, 0.12, 0.0f, {1.0f, 1.0f, 0.0f}, 42.0, 1.7 }));
    jupiter.addMoon(Planet::createFromRealData({ "Europa", 1560.0, 0.15, 0.0f, {0.9f, 0.9f, 0.8f}, 85.0, 3.5 }));
    solarSystem.push_back(jupiter);

    // --- 7. SAO THỔ (Saturn) ---
    // Rad: 58,232km, Dist: 9.58 AU
    RealSpaceData satData = { "Saturn", 58232.0, 9.58, 26.7f, {0.9f, 0.8f, 0.5f}, 10.7, 10759.0 };
    Planet saturn = Planet::createFromRealData(satData);
    saturn.addMoon(Planet::createFromRealData({ "Titan", 2574.0, 0.18, 0.0f, {0.9f, 0.7f, 0.1f}, 382.0, 15.9 }));
    solarSystem.push_back(saturn);

    // --- 8. SAO THIÊN VƯƠNG (Uranus) ---
    // Rad: 25,362km, Dist: 19.22 AU
    RealSpaceData uraData = { "Uranus", 25362.0, 19.22, 97.8f, {0.6f, 0.8f, 0.9f}, 17.2, 30687.0 };
    solarSystem.push_back(Planet::createFromRealData(uraData));

    // --- 9. SAO HẢI VƯƠNG (Neptune) ---
    // Rad: 24,622km, Dist: 30.05 AU
    RealSpaceData nepData = { "Neptune", 24622.0, 30.05, 28.3f, {0.2f, 0.4f, 0.9f}, 16.1, 60190.0 };
    solarSystem.push_back(Planet::createFromRealData(nepData));
}
void display() {
    // Clear display and Bộ nhớ độ sâu
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set Camera
    gluLookAt(0.0f, 38.0f, 38.0f,  // eye
              0.0f, 0.0f, 0.0f,    // forward
              0.0f, 1.0f, 0.0);    // up

    // For in SolarSys, drawOrbit + drawPlanet
    for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
        solarSystem[planetIndex].drawOrrbit();
        solarSystem[planetIndex].drawPlanet();
    }

    // Đẩy hình ảnh từ bộ nhớ ra display 
    glutSwapBuffers();
}

void timer(int value) {
    for (int planetIndex = 0; planetIndex < solarSystem.size(); planetIndex++) {
        solarSystem[planetIndex].updateTime();
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1200.0 / 800.0, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();

    return 0;
}