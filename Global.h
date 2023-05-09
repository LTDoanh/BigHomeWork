#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Constants.h"
#include "LTexture.h"
#include "Player.h"
#include "HScores.h"

// Khai báo các biến toàn cục
extern SDL_Window* window; // Cửa sổ chính
extern SDL_Renderer* renderer; // Bộ vẽ
extern SDL_Rect buttons[BUTTON_NUM]; // Mảng các nút
extern std::vector<int> sequence; // Chuỗi các nút cần nhấn
extern int level; // Cấp độ hiện tại
extern int index; // Chỉ số của nút cần nhấn tiếp theo
extern bool showSequence; // Biến kiểm tra có đang hiển thị chuỗi hay không
//extern bool clicked; // Biến kiểm tra có đang click chuột vào nút hay không
//extern int clickedIndex; // Chỉ số nút đã nhấn
extern Uint32 startTime; // Thời điểm bắt đầu hiển thị chuỗi
extern bool gameOver; // Biến kiểm tra trò chơi kết thúc hay chưa
extern int score; // Điểm số hiện tại
extern int timeLeft; // Thời gian còn lại
extern bool running;
extern bool isMenu;
extern bool isGuide;
extern bool isSetting;
extern bool isEasy;
extern bool isDefault;
extern bool isNormal;
extern bool isHard;
extern bool isRanking;
extern bool isReset;
extern bool isMute;
extern bool isPause;
extern bool isHighScore;
extern bool readHS;
extern string nameOfPlayer;

extern std::vector<Player> HighScores;

extern TTF_Font* font; // Font chữ
extern Mix_Music* music; // Nhạc nền của game
extern Mix_Chunk* beepSound; // Âm thanh khi nhấn nút
extern Mix_Chunk* wrongSound; // Âm thanh khi nhấn sai nút

#endif // GLOBAL_H_INCLUDED
