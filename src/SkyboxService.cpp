#include "../include/SkyboxService.h"
#include "../include/TextureUtils.h"

GLuint skyBoxTextures[6];
struct Vec3i {
	int x, y, z;
};

void initSkybox() {
    skyBoxTextures[0] = loadTexture("assets/textures/right.png");
    skyBoxTextures[1] = loadTexture("assets/textures/left.png");
    skyBoxTextures[2] = loadTexture("assets/textures/top.png");
    skyBoxTextures[3] = loadTexture("assets/textures/bot.png");
    skyBoxTextures[4] = loadTexture("assets/textures/front.png");
    skyBoxTextures[5] = loadTexture("assets/textures/back.png");
}

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