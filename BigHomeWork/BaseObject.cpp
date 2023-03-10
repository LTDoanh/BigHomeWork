#include "BaseObject.h"


BaseObject::BaseObject()
{
    rect_.x = 0;
    rect_.y = 0;
    p_object_ = nullptr;
}
BaseObject::~BaseObject()
{
    if (p_object_ != nullptr) {
        delete p_object_;
        p_object_ = nullptr;
    }
}

bool BaseObject::LoadImg(const char* file_name)
{
    p_object_ = LoadImage(file_name);
    if (p_object_ == nullptr) return 0;
    return 1;
}

void BaseObject::Show(SDL_Surface* dst)
{
    if (p_object_ != nullptr) {
        ApplySurface(p_object_, dst, rect_.x, rect_.y);
    }
}
