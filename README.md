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

## 🟢 CHẶNG 1: HOÀN THIỆN LOGIC HỆ THỐNG (THE SKELETON)
*Mục tiêu: Xử lý triệt để bài toán "thằng này quay quanh thằng kia" bằng Ma trận phân cấp.*

- [x] **OOP Setup:** Khai báo Class `Planet`, quản lý thuộc tính (Radius, Distance, Speed).
- [x] **Basic Draw:** Vẽ Quỹ đạo (`GL_LINE_LOOP`) và Khối cầu (`glutSolidSphere`).
- [x] **Frame Control:** Khóa 60 FPS bằng `glutTimerFunc` (mỗi 16ms cập nhật một lần).
- [x] **Hierarchical Modeling (Nhiệm vụ trọng tâm):** - Áp dụng lồng `glPushMatrix` và `glPopMatrix` để vẽ **Mặt Trăng quay quanh Trái Đất**.
    - *Logic:* Tọa độ Mặt Trăng phải phụ thuộc vào tọa độ hiện tại của Trái Đất.
- [x] **Saturn's Ring:** Sử dụng `gluDisk` để vẽ vành đai bao quanh Sao Thổ.

---

## 🟡 CHẶNG 2: CAMERA & TƯƠNG TÁC (THE EYES & HANDS)
*Mục tiêu: Biến một bức tranh tĩnh thành một vũ trụ có thể khám phá tự do.*

- [x] **Hệ thống Camera 3D:**
    - Sử dụng `gluLookAt` kết hợp tọa độ cầu ($r, \theta, \phi$) để xoay camera quanh tâm hệ.
    - Chế độ **Zoom**: Thay đổi khoảng cách camera bằng con lăn chuột hoặc phím `W/S`.
- [x] **Keyboard Interaction:**
    - Điều khiển hướng nhìn bằng phím mũi tên hoặc `A/D`.
    - Phím `Space`: Tạm dừng/Tiếp tục chuyển động (Pause/Resume).
- [x] **Planet Focus Mode (Tính năng Pro):**
    - Nhấn phím `1-9` để camera "khóa mục tiêu" vào hành tinh tương ứng. 
    - Khi hành tinh bay, camera tự động bám đuổi theo tọa độ của nó.

---

## 🔴 CHẶNG 3: ÁNH SÁNG & VẬT LIỆU (THE LIGHT)
*Mục tiêu: Biến các khối màu bẹt thành khối 3D có chiều sâu.*

- [x] **Kích hoạt Lighting:** Bật `GL_LIGHTING` và `GL_LIGHT0`.
- [x] **Nguồn sáng điểm (Point Light):** Đặt đèn tại tọa độ $(0,0,0)$ (Tâm Mặt Trời).
    - Tạo hiệu ứng mặt hướng về Mặt Trời thì sáng, mặt đối diện thì tối (Ngày/Đêm).
- [x] **Cấu hình Material:**
    - Sử dụng `glMaterialfv` thay cho `glColor` (vì Lighting làm vô hiệu hóa Color thông thường).
    - Quy định độ bóng (`GL_SHININESS`) và màu sắc khuếch tán (`GL_DIFFUSE`).

---

## 🔵 CHẶNG 4: TEXTURE & SKYBOX (THE SKIN)
*Mục tiêu: Đưa đồ họa lên mức độ chân thực với hình ảnh vệ tinh.*

- [x] **Texture Mapping:**
    - Tích hợp thư viện `stb_image.h` để load ảnh `.jpg`/`.png`.
    - Dùng `gluSphere` (thay cho `glutSolidSphere`) để có thể trải bản đồ bề mặt (Earth, Mars...) lên khối cầu.
    ( Chưa thể dán phần ảnh vành đai lên vành đai sao thổ)
- [ ] **Skybox (Vòm sao):** Vẽ một khối lập phương khổng lồ bao quanh vũ trụ, dán ảnh dải ngân hà vào mặt trong.
- [ ] **Emission Light:** Làm cho Mặt Trời tự phát sáng rực rỡ (không bị ảnh hưởng bởi bóng tối của chính nó).

---

## 🟣 CHẶNG 5: UI & HOÀN THIỆN (THE POLISH)
*Mục tiêu: Trình bày thông tin và tối ưu hóa trước khi nộp đồ án.*

- [ ] **Heads-up Display (HUD):**
    - Hiển thị tên hành tinh đang Focus lên màn hình bằng `glutBitmapCharacter`.
    - In thông số (Vận tốc, Khoảng cách) ra màn hình Console hoặc giao diện Overlay.
- [ ] **Refactoring:** Tối ưu hóa vòng lặp, giải phóng bộ nhớ (Vector/Texture).
- [ ] **Documentation:** Viết hướng dẫn sử dụng phím bấm để thầy giáo dễ chấm điểm.

## 🚀 Hướng Dẫn Chạy (How to Run)

```bash
1. Clone repository này về máy.
2. Mở file `SolarSystem_3D.sln` bằng Visual Studio.
3. Chờ NuGet tự động khôi phục các packages (nupengl).
4. Nhấn `F5` hoặc nút `Local Windows Debugger` để biên dịch và chạy.
````
