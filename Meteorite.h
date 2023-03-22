#pragma once

#include "Project_Base.h"
#include "LTexture.h"
#include "GlobalVariables.h"

class Meteorite
{
public:
    // Các hàm cơ bản
    Meteorite();

    void update();

    void render();

    bool checkCollision(int bulletX, int bulletY);

    int getX();
    int getY();

    bool isAlive();

    void setAlive(bool alive);
private:
    // Biến lưu vị trí và góc xoay
    int m_x;
    int m_y;
    double m_angle;

    // Biến lưu trạng thái sống
    bool m_alive;
};

// METEORITE_H_INCLUDED
