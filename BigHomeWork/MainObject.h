#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED
#pragma once

#include "SDL_utils.h"
#include "BaseObject.h"

#define WIDTH_MAIN 80
#define HEIGHT_MAIN 89

class MainObject : public BaseObject
{
protected:
    int x_;
    int y_;
public:
    MainObject();
    ~MainObject();
    void InputAction(SDL_Event e);
    void Move();
};

#endif // MAINOBJECT_H_INCLUDED
