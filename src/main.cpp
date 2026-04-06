#include"../include/TextureUtils.h"
#include "../include/SkyboxService.h"
#include "../include/Camera.h"
#include "../include/SceneManager.h"
#include "../include/Planet.h"
using namespace std;

Camera mainCam;
SceneManager scene;

// Function tính toán vị trí camera
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float targetX = 0.0f, targetY = 0.0f, targetZ = 0.0f;
    // Hàm xử lý lấy tọa độ tại hành tinh đang focus
    scene.getCameraTarget(targetX, targetY, targetZ);
    //Tính toán vị trí Mắt Camera
    // Thay vì tính từ gốc 0,0,0, ta cộng thêm targetX, targetY, targetZ vào
    // => Sợi dây Camera lúc này được cột vào hành tinh mục tiêu!
    float camX = targetX + mainCam.camRadius * cos(mainCam.camPitch) * sin(mainCam.camYaw);
    float camY = targetY + mainCam.camRadius * sin(mainCam.camPitch);
    float camZ = targetZ + mainCam.camRadius * cos(mainCam.camPitch) * cos(mainCam.camYaw);

    // Set Camera
    gluLookAt(camX, camY, camZ,   // Mắt camera đang nằm ở X, Y, Z vừa tính
        targetX, targetY, targetZ,   // Nhìn thẳng vào vị trí hành tinh (x, y, z)
        0.0f, 1.0f, 0.0f);  // Quy định trục Y là hướng lên trời

    drawSkybox(camX, camY, camZ);

    GLfloat light_pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // Vẽ hệ mặt trời 
    scene.drawAll();

    // Đẩy hình ảnh từ bộ nhớ ra display 
    glutSwapBuffers();
}

// Function cập nhật khung hình
void timer(int value) {
    // hàm update time từ struct sceneManager
    scene.updateTime();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Function lắng nghe bàn phím thường
void keyboard(unsigned char key, int x, int y) {
    // Hàm xử lý được gắn trong struct của sceneManager, ko phải bên trong Camera do dính đến danh sách hành tinh
    scene.handleKeyboard(key, mainCam);
    glutPostRedisplay();
}
// Function lắng nghe phím mũi tên 
void specialKeys(int key, int x, int y) {
    mainCam.handleSpecialKeys(key, x, y);
    glutPostRedisplay();
}
// Function zoom in-out khi lăn chuột và cập nhật tọa độ lastX,Y nếu nhấn chuột trái
void mouseClick(int button, int state, int x, int y) {
    mainCam.handleMouseClick(button, state, x, y);
    glutPostRedisplay();
}
// Function Đổi góc khi nhấn tọa độ lastX,Y thay đổi
void mouseMotion(int x, int y) {
    mainCam.handleMouseMotion(x, y);
    glutPostRedisplay();
}

// Function tạo các hành tinh và lưu vào mảng Solar Systems
void initPlanets() {
    // Hàm dài ngoằng 1 đống hành tinh ở bên SceneManager
    scene.initPlanets();
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
    
    // gàn vào nguồn sáng
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
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
    scene.initPlanets();
    initSkybox();

    // In bảng điều khiển lần đầu
    scene.printDashBoard();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    // ĐĂNG KÝ CÁC HÀM XỬ LÝ
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1200.0 / 800.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glutMainLoop();

    return 0;
}