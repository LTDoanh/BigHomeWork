#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <SDL.h>

// Khai báo các hằng số
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BUTTON_SIZE = 100;
const int BUTTON_GAP = 20;
const int BUTTON_ROW = 4;
const int BUTTON_COL = 4;
const int BUTTON_NUM = BUTTON_ROW * BUTTON_COL;
const int DELAY_TIME = 1000; // Thời gian chờ giữa các lượt
const int FLASH_TIME = 500; // Thời gian nhấp nháy của nút
const SDL_Color BG_COLOR = {0, 0, 0, 255}; // Màu nền
const SDL_Color BUTTON_COLOR = {238, 64, 240, 255}; // Màu nút
const SDL_Color FLASH_COLOR = {255, 255, 255, 255}; // Màu nhấp nháy
const SDL_Color TEXT_COLOR = {255, 255, 255, 255}; // Màu chữ
const SDL_Color CLICKED_COLOR = {255, 255, 0, 255}; // Màu nhấn nút

#endif // CONSTANTS_H_INCLUDED
