#include "../../include/engine/object.hpp"

SDL_FPoint Object::getPos() {
    return mPos;
}

SDL_FRect Object::getHitBox() {
    return mHitBox;
}