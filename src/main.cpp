#include <GL/glut.h>
#include <vector>
#include "../include/Planet.h"
using namespace std;
vector <Planet> solarSystem;

void initPlanets() {

    //	Planet(string na, float rad, float dist, float tilt,
    //		float rCol, float gCol, float bCol, // Màu sắc RGB cho biến color
    //		float orbSpeed, float rotSpeed

    Planet Sun = Planet("Sun", 1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.2f);
    solarSystem.push_back(Sun);
    Planet Mercury = Planet("Mercury", 0.2f, 2.5f, 7.0f, 0.7f, 0.7f, 0.7f, 1.5f, 0.5f);
    solarSystem.push_back(Mercury);
    Planet Venus = Planet("Venus", 0.35f, 4.0f, 177.0f, 0.9f, 0.6f, 0.2f, 1.0f, 0.3f);
    solarSystem.push_back(Venus);
    Planet Earth = Planet("Earth", 0.4f, 6.0f, 23.5f, 0.2f, 0.3f, 1.0f, 0.7f, 1.0f);
    solarSystem.push_back(Earth);
    Planet Mars = Planet("Mars", 0.3f, 8.0f, 25.0f, 1.0f, 0.2f, 0.0f, 0.5f, 0.9f);
    solarSystem.push_back(Mars);
    Planet Jupiter{ "Jupiter", 1.0f, 11.0f, 3.1f, 0.8f, 0.6f, 0.4f, 0.3f, 2.5f };
    solarSystem.push_back(Jupiter);
    Planet Saturn{ "Saturn", 0.9f, 14.0f, 26.7f, 0.9f, 0.8f, 0.5f, 0.2f, 2.2f };
    solarSystem.push_back(Saturn);
    Planet Uranus{ "Uranus", 0.6f, 17.0f, 97.8f, 0.6f, 0.8f, 0.9f, 0.15f, 1.5f };
    solarSystem.push_back(Uranus);
    Planet Neptune{ "Neptune", 0.6f, 20.0f, 28.3f, 0.2f, 0.4f, 0.9f, 0.1f, 1.4f };
    solarSystem.push_back(Neptune);

}
void display() {
    // Clear display and Bộ nhớ độ sâu
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set Camera
    gluLookAt(0.0f, 15.0f, 20.0f,  // eye
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
    initPlanets();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1200.0 / 800.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();

    return 0;
}