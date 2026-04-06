#pragma once
#include <vector>
#include "Planet.h"
#include "Camera.h"

using namespace std;

struct SceneManager {
    vector <Planet> solarSystem;    // DANH SÁCH CÁC HÀNH TINH
    bool isPaused = false;          // TOGGLE XUAY - PAUSE
    int currentPLanetIndex = 0;     // HÀNH TINH ĐANG CÓ TÂM TRÙNG VỚI TÂM HỆ TỌA ĐỘ ( ĐANG QUAN SÁT) 
    int currentMoonIndex = -1;      // QUAN SÁT MẶT TRĂNG CỦA HÀNH TINH MẸ NẾU != -1

    // Function tạo các hành tinh
    void initPlanets();

    // Function Hiển thị thông tin lên Console
    void printDashBoard();

    // Function vẽ lại màn hình theo TG - cập nhật khung hình
    void updateTime();

    // Tính toán vị trí mới của camera dựa theo hành tinh tele
    void getCameraTarget(float& targetX, float& targetY, float& targetZ);

    // Xử lý các sự kiện lắng nghe bàn phím thường
    void handleKeyboard(unsigned char key, Camera& cam);

    // Vẽ các hành tinh 
    void drawAll();
};