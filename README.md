# 🌍 C++ OpenGL: 3D Solar System Simulation (Mô Phỏng Hệ Mặt Trời 3D)

**GVHD:** ThS. Đỗ Trí Nhựt.

**Môn học:** Đồ họa máy tính (Computer Graphics) - Học kỳ 2, Năm 3.

**Ngôn ngữ & Thư viện:** C++, OpenGL (GLUT/GLEW).

**Môi trường phát triển:** Visual Studio 2026.

## 🎯 Mục Tiêu Dự Án

Dự án này là tiểu luận cuối kỳ nhằm ứng dụng các lý thuyết cốt lõi của Đồ họa máy tính vào thực tiễn, bao gồm:

- **Phép biến đổi 3D (3D Transformations):** Xoay (Rotation), Tịnh tiến (Translation).
- **Ma trận phân cấp (Hierarchical Modeling):** Sử dụng ma trận ngăn xếp (`glPushMatrix`, `glPopMatrix`) để mô phỏng quỹ đạo lồng nhau (Mặt Trăng quay quanh Trái Đất, Trái Đất quay quanh Mặt Trời).
- **Camera & Phép chiếu (Viewing & Projection):** Áp dụng `gluLookAt` và `gluPerspective` để tạo hệ thống camera quan sát không gian.
- **Ánh sáng & Vật liệu (Illumination & Shading):** Ứng dụng mô hình chiếu sáng Phong (Phong Reflection Model) để tạo khối 3D chân thực.
- **Khử mặt khuất (Hidden Surface Removal):** Sử dụng Z-Buffer (`GL_DEPTH_TEST`).

## ⚙️ Các Chức Năng Cốt Lõi (Features)

1. **Render 3D:** Khởi tạo và vẽ hệ thống Mặt Trời cùng 8 hành tinh trong không gian 3 chiều.
2. **Animation (60 FPS):** Các hành tinh tự động quay quanh trục và quay quanh Mặt Trời theo tỷ lệ thời gian được lập trình bằng `glutTimerFunc`.
3. **Tương tác Camera:** - Điều khiển góc nhìn bằng chuột và bàn phím.
   - Các phím số (1-8) để di chuyển Camera focus vào từng hành tinh cụ thể.
4. **Console UI:** Hiển thị thông số của hành tinh (Khối lượng, Khoảng cách) - Chức năng nâng cao.

## 🗺️ Lộ Trình Phát Triển (Roadmap)

- [x] **Chặng 1:** Khởi tạo dự án, setup thư viện nupengl qua NuGet, cấu hình Git & `.gitignore`. Xây dựng cấu trúc hướng đối tượng (OOP) `Class Planet`.
- [ ] **Chặng 2:** Khởi tạo mảng dữ liệu 8 hành tinh. Code vòng lặp Animation, vẽ quỹ đạo (Orbit) và khối cầu. (Mục tiêu báo cáo tiến độ 28/3).
- [ ] **Chặng 3:** Tích hợp hệ thống Camera tương tác (Phím/Chuột).
- [ ] **Chặng 4:** Bật hệ thống Lighting và dán Texture (Bản đồ bề mặt) cho từng hành tinh để hoàn thiện tiểu luận cuối kỳ.

## 🚀 Hướng Dẫn Chạy (How to Run)

```bash
1. Clone repository này về máy.
2. Mở file `SolarSystem_3D.sln` bằng Visual Studio.
3. Chờ NuGet tự động khôi phục các packages (nupengl).
4. Nhấn `F5` hoặc nút `Local Windows Debugger` để biên dịch và chạy.
```
