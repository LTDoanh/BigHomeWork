#include "MainObject.h"

MainObject::MainObject()
{
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN;
    rect_.h = HEIGHT_MAIN;
    x_ = 0;
    y_ =0;
}

MainObject::~MainObject(){}

void MainObject::InputAction(SDL_Event e)
{

}

void MainObject::Move()
{

}
