#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Project_Base.h"
#include "LTexture.h"
#include "Ship.h"
#include "Meteorite.h"
#include "Bullet.h"

class Game
{
public:
    /** Hàm khởi tạo các thành phần cơ bản của SDL **/
    bool init();

    /** Hàm tải các tài nguyên cho game **/
    bool loadMedia();

    /** Hàm giải phóng các thành phần cơ bản của SDL **/
    void close();

    /** Hàm cập nhật trạng thái của game **/
    void update();

    /** Hàm xử lí sự kiện **/
    void handleEvents();

    /** Hàm vẽ các đối tượng lên màn hình **/
    void render();

    bool quit = false;

private:
    int score = 0;

    TTF_Font* font = nullptr;
    Mix_Music* music = nullptr;
    Mix_Chunk* shoot_sound = nullptr;
    Mix_Chunk* explode_sound = nullptr;

    LTexture backgroundTexture;
    LTexture gameOverTexture;
    LTexture shipTexture;
    LTexture meteoriteTexture;
    LTexture bulletTexture;

    Ship ship;
};

#endif // GAME_H_INCLUDED
