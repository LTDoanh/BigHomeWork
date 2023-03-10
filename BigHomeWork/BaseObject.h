#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED
#pragma once

#include "SDL_utils.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void Show(SDL_Surface* dst);
    bool LoadImg(const char* file_name);

    void SetRect(int x, int y) {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect GetRect() {return rect_;}
    SDL_Surface* GetObject() {return p_object_;}
protected:
    SDL_Rect rect_;
    SDL_Surface* p_object_;
};

#endif // BASEOBJECT_H_INCLUDED
