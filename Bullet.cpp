#include "Bullet.h"

Bullet::Bullet(int x, int y)
{
    b_x = x;
    b_y = y;
    b_alive = true;
}

void Bullet::update()
{
    b_y -= BULLET_SPEED;
    if (b_y < 0)
    {
        b_alive = false;
    }
}

// Hàm vẽ lên màn hình
void Bullet::render()
{
    bulletTexture.render(b_x - bulletTexture.getWidth() / 2, b_y - bulletTexture.getHeight() / 2);
}

// Hàm lấy vị trí x
int Bullet::getX()
{
    return b_x;
}

// Hàm lấy vị trí y
int Bullet::getY()
{
    return b_y;
}

// Hàm lấy trạng thái sống
bool Bullet::isAlive()
{
    return b_alive;
}

// Hàm thiết lập trạng thái sống
void Bullet::setAlive(bool alive)
{
    b_alive = alive;
}
