#pragma once
#include <GL/glut.h>

struct Vec3i;

// Function lấy 6 mặt của Skybox
void initSkybox();
// Function ghép ảnh vào hệ trục tạo hình lập phương
void graftFace(float r, GLuint texture, Vec3i LB, Vec3i RB, Vec3i TR, Vec3i TL);

// Function vẽ Sky Box 
void drawSkybox(float camX, float camY, float camZ);