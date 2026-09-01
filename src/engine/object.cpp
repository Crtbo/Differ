#include "../../include/engine/object.hpp"

SDL_FPoint Object::getPos() {
    return mPos;
}

SDL_FRect Object::getHitBox() {
    return mHitBox;
}

void Object::setPos(float x, float y) {
    mPos.x = x;
    mPos.y = y;
}

void Object::setVel(float x, float y) {
    mVel.x = x;
    mVel.y = y;
}

void Object::setBox(float w, float h) {
    updateBox();
    mHitBox.w = w;
    mHitBox.h = h;
}

void Object::updateBox() {
    mHitBox.x = mPos.x;
    mHitBox.y = mPos.y;
}