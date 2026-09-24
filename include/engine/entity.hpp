#pragma once
#include <SDL3/SDL.h>

class Entity {
    protected:
        SDL_FPoint mPos;
        SDL_FPoint mVel;
        SDL_FRect mHitBox;
    
    public:
        SDL_FPoint getPos();
        SDL_FRect getHitBox();
        void setPos(float, float);
        void setVel(float, float);
        virtual void setBox(float, float);
        virtual void updateBox();
};