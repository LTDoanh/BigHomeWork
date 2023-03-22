#include "Ship.h"

Ship::Ship()
{
    s_x = SCREEN_WIDTH / 2;
    s_y = SCREEN_HEIGHT - 100;
    s_alive = true;
}

// Hàm cập nhật trạng thái
void Ship::update()
{
    // Lấy trạng thái của bàn phím
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    // Di chuyển tàu theo phím bấm
    if (keyState[SDL_SCANCODE_LEFT]) {
        s_x -= SHIP_SPEED;
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
        s_x += SHIP_SPEED;
    }
    if (keyState[SDL_SCANCODE_UP]) {
        s_y -= SHIP_SPEED;
    }
    if (keyState[SDL_SCANCODE_DOWN]) {
        s_y += SHIP_SPEED;
    }

    // Giới hạn vị trí của tàu trong màn hình
    if(s_x < 0) {
        s_x = 0;
    }
    if(s_x > SCREEN_WIDTH - shipTexture.getWidth()) {
        s_x = SCREEN_WIDTH - shipTexture.getWidth();
    }
    if(s_y < 0) {
        s_y = 0;
    }
    if(s_y > SCREEN_HEIGHT - shipTexture.getHeight()) {
        s_y = SCREEN_HEIGHT - shipTexture.getHeight();
    }
}

// Hàm vẽ lên màn hình
void Ship::render()
{
    shipTexture.render(s_x, s_y);
}

// Hàm bắn đạn
void Ship::shoot()
{
    // Tạo đối tượng đạn mới và thêm vào vector bullets
    Bullet* bullet = new Bullet(s_x + shipTexture.getWidth() / 2, s_y);
    bullets.push_back(bullet);

    // Phát âm thanh bắn đạn
    Mix_PlayChannel(-1, shoot_sound, 0);
}

// Hàm kiểm tra va chạm với thiên thạch
bool Ship::checkCollision(int meteoriteX, int meteoriteY)
{
    int dx = s_x + shipTexture.getWidth() / 2 - meteoriteX;
    int dy = s_y + shipTexture.getHeight() / 2 - meteoriteY;
    int distance = sqrt(dx*dx + dy*dy);
    if(distance < meteoriteTexture.getWidth() / 2) {
        return true;
    }
    else {
        return false;
    }
}

int Ship::getX()
{
    return s_x;
}

int Ship::getY()
{
    return s_y;
}

// Hàm lấy trạng thái sống
bool Ship::isAlive()
{
    return s_alive;
}

// Hàm thiết lập trạng thái sống
void Ship::setAlive(bool alive)
{
    s_alive = alive;
}
