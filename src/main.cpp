#include <GL/glut.h>

void display() {
    // Xóa màn hình và tô bằng màu nền (hiện tại là đen)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Đẩy hình ảnh ra màn hình
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // 1. Khởi tạo GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // 2. Kích thước và Tên cửa sổ
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("He Mat Troi 3D - Setup Thanh Cong");

    // 3. Màu nền vũ trụ (Màu Đen)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 4. Đăng ký hàm vẽ và chạy vòng lặp
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}