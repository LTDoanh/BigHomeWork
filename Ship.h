#pragma once

#include "Project_Base.h"
#include "LTexture.h"
#include "GlobalVariables.h"
#include "Bullet.h"
#include "Meteorite.h"

static vector<Meteorite*> meteorites;
static vector<Bullet*> bullets(0,0);

class Ship {
public:
    Ship();

    void update();

    void render();

    void shoot();

    bool checkCollision(int meteoriteX,int meteoriteY);

    bool isAlive();

    int getX();
    int getY();

    void setAlive(bool alive);
private:
    // Biến lưu vị trí
    int s_x;
    int s_y;

    // Biến lưu trạng thái sống
    bool s_alive;
};

// SHIP_H_INCLUDED
