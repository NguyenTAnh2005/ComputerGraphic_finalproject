#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#include "../include/TextureUtils.h"
#include <iostream>
using namespace std;
// FUNCTION - Đọc ảnh, nạp ảnh lên GPU, cấp id --> Khi dán ảnh cho hành tinh chỉ cần gọi ID
// Code nâng cao - Copy chat 
GLuint loadTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 4) format = GL_RGBA;
        //glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);

        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
        cout << "[SUCCESS] Loaded: " << filename << " (" << width << "x" << height << ")" << endl;
    }
    else {
        cout << "[ERROR] Failed to load texture: " << filename << endl;
    }
    stbi_image_free(data);
    return textureID;
}