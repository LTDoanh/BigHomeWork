#pragma once

#include "Project_Base.h"
#include "LTexture.h"
#include "GlobalVariables.h"

class Bullet
{
public:
    Bullet(int x, int y);

    void update();

    void render();

    int getX();
    int getY();

    bool isAlive();

    void setAlive(bool alive);
private:
    // Biến lưu vị trí
    int b_x;
    int b_y;

    // Biến lưu trạng thái sống
    bool b_alive;
};

// BULLET_H_INCLUDED
