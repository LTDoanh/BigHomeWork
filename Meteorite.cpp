#include "Meteorite.h"

// Hàm khởi tạo
Meteorite::Meteorite()
{
    m_x = rand() % SCREEN_WIDTH;
    m_y = -100;
    m_angle = 0;
    m_alive = true;
}

// Hàm cập nhật trạng thái
void Meteorite::update()
{
    m_y += METEORITE_SPEED;
    m_angle += 0.1;
    if (m_y > SCREEN_HEIGHT) {
        m_alive = false;
    }
}

// Hàm vẽ lên màn hình
void Meteorite::render()
{
    meteoriteTexture.render(m_x - meteoriteTexture.getWidth() / 2, m_y - meteoriteTexture.getHeight() / 2);
}

// Hàm kiểm tra va chạm với đạn
bool Meteorite::checkCollision(int bulletX, int bulletY)
{
    int dx = m_x - bulletX;
    int dy = m_y - bulletY;
    int distance = sqrt(dx * dx + dy * dy);
    if (distance < meteoriteTexture.getWidth() / 2) return true;
    else return false;
}

int Meteorite::getX()
{
    return m_x;
}

int Meteorite::getY()
{
    return m_y;
}

// Hàm lấy trạng thái sống
bool Meteorite::isAlive()
{
    return m_alive;
}

// Hàm thiết lập trạng thái sống
void Meteorite::setAlive(bool alive)
{
    m_alive = alive;
}
