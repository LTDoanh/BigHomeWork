#pragma once

#include "Project_Base.h"
#include "LTexture.h"
#include "GlobalVariables.h"
#include "SDL_Utils.h"

// Hàm giải phóng các thành phần cơ bản của SDL
bool init();

// Hàm tải texture từ một file ảnh
SDL_Texture* loadTexture(string path);

// Hàm tải âm nhạc từ một file âm thanh
Mix_Music* loadMusic(string path);

// Hàm tải âm thanh hiệu ứng từ một file âm thanh
Mix_Chunk* loadSound(string path);

// Hàm tải font chữ từ một file font
TTF_Font* loadFont(string path, int size);

// Hàm tải các tài nguyên cho game
bool loadMedia();

// Hàm giải phóng các thành phần cơ bản của SDL
void close();

// COMMONFUNCTION_H_INCLUDED
