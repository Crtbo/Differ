#include "../../include/engine/entity.hpp"

SDL_FPoint Entity::getPos() {
    return mPos;
}

SDL_FRect Entity::getHitBox() {
    return mHitBox;
}

void Entity::setPos(float x, float y) {
    mPos.x = x;
    mPos.y = y;
}

void Entity::setVel(float x, float y) {
    mVel.x = x;
    mVel.y = y;
}

void Entity::setBox(float w, float h) {
    updateBox();
    mHitBox.w = w;
    mHitBox.h = h;
}

void Entity::updateBox() {
    mHitBox.x = mPos.x;
    mHitBox.y = mPos.y;
}