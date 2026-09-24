#pragma once
#include "entity.hpp"
#include "tile.hpp"
#include "../other/const.hpp"
#include <vector>

class Player : public Entity
{
    private:
        SDL_FRect mFeetBox;
        int mModifier;
        int mPushBack;
        bool mGrounded;
        bool mSliding;
        int mCoyote;

    public:
        Player();
        void handleEvent(SDL_Event &);
        void move(std::vector <Tile> &);
        void render(SDL_FRect &, Texture &);
        void setCamera(SDL_FRect &, int, int);
        void setBox(float, float) override;
        void updateBox() override;
};