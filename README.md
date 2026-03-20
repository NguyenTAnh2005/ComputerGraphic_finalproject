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

## Cấu trúc thư mục

```bash
├── 📁 Final
├── 📁 assets
│   └── 📁 textures
├── 📁 include
│   └── ⚡ Planet.h
├── 📁 packages
│   ├── 📁 nupengl.core.0.1.0.1
│   │   └── ⚙️ .signature.p7s
│   └── 📁 nupengl.core.redist.0.1.0.1
│       └── ⚙️ .signature.p7s
├── 📁 src
│   └── ⚡ main.cpp
├── ⚙️ .gitattributes
├── ⚙️ .gitignore
├── 📄 Final.slnx
├── 📄 Final.vcxproj
├── 📄 Final.vcxproj.filters
├── 📝 README.md
└── ⚙️ packages.config
```


## 🗺️ Lộ Trình Phát Triển (Roadmap)

### **Chặng 1: Thiết kế Kiến trúc OOP & Khởi tạo **

- [x] Setup Project Visual Studio C++, tích hợp thư viện `nupengl.core` qua NuGet.
- [x] Cấu hình Git Repository và `Visual Studio .gitignore`.
- [x] Áp dụng Lập trình hướng đối tượng (OOP), định nghĩa `Class Planet` quản lý các thuộc tính độc lập (Bán kính, Khoảng cách, Tốc độ, Màu sắc).
- [x] Khởi tạo mảng dữ liệu mô phỏng 8 hành tinh dựa trên tỷ lệ thu nhỏ tương đối từ Wikipedia.

### **Chặng 2: Rendering & Animation - **

- [x] Xây dựng hàm `drawOrbit()` sử dụng `GL_LINE_LOOP` để vẽ đường quỹ đạo.
- [x] Xây dựng hàm `drawPlanet()` sử dụng `glutSolidSphere` để dựng hình khối cầu.
- [x] Sử dụng `glutTimerFunc` tạo vòng lặp thời gian thực (Real-time Animation ~60FPS) mượt mà.
- [ ] Áp dụng Ma trận phân cấp (`glPushMatrix`, `glPopMatrix`) để xử lý bài toán hệ quỹ đạo lồng nhau.
- [ ] Vẽ thêm các hành tinh phụ như (the moon, ....)

### **Chặng 3: Camera & Tương tác Người dùng **

- [ ] Tích hợp Phép chiếu phối cảnh (`gluPerspective`) và Ma trận quan sát (`gluLookAt`).
- [ ] Bắt sự kiện bàn phím (Phím mũi tên / WASD) để điều khiển Camera bay quanh không gian vũ trụ.
- [ ] **Tính năng Focus & HUD:** Gắn phím số `1-8` để tự động dịch chuyển Camera bám theo hành tinh tương ứng, đồng thời xuất thông tin khoa học của hành tinh đó ra màn hình Console.

### **Chặng 4: Illumination & Texture Mapping **

- [ ] Kích hoạt hệ thống Ánh sáng Phong (`GL_LIGHTING`, `GL_LIGHT0`), đặt nguồn sáng tại tâm Mặt Trời.
- [ ] Cấu hình vật liệu khuếch tán (`GL_DIFFUSE`) để tạo hiện tượng ngày/đêm trên bề mặt hành tinh.
- [ ] Tích hợp thư viện đọc ảnh (vd: `stb_image.h`) để load bản đồ vệ tinh (`.jpg`).
- [ ] Dùng `Texture Mapping` bọc lớp vỏ địa lý lên các khối cầu, nâng cấp đồ họa từ dạng khối màu trơn lên mức độ chân thực.

## 🚀 Hướng Dẫn Chạy (How to Run)

```bash
1. Clone repository này về máy.
2. Mở file `SolarSystem_3D.sln` bằng Visual Studio.
3. Chờ NuGet tự động khôi phục các packages (nupengl).
4. Nhấn `F5` hoặc nút `Local Windows Debugger` để biên dịch và chạy.
````
