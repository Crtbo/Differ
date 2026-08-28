#pragma once
#include <SDL3/SDL.h>

class Object {
    protected:
        int mVel;
        SDL_FPoint mPos;
        SDL_FRect mHitBox;
    
    public:
        SDL_FPoint getPos();
        SDL_FRect getHitBox();
        void setVel(int);
        void setPos(float, float);
        void setHitBox(float, float);
        void updateBox();
};