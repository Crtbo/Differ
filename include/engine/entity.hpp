#pragma once
#include <SDL3/SDL.h>

class Entity {
    protected:
        SDL_FPoint mPos;
        SDL_FPoint mVel;
        SDL_FRect mHitBox;
    
    public:
        virtual void setPos(float, float) = 0;
        virtual void setVel(float, float) = 0;
        virtual void setBoxSize(float, float) = 0;
        virtual void setBoxPos() = 0;
};