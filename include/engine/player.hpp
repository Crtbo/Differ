#pragma once
#include "object.hpp"
#include "tile.hpp"
#include "../other/const.hpp"
#include <vector>

class Player : public Object
{
    private:
        SDL_FRect mFeetBox;
        int mSpeed;
        bool mGrounded;
        bool mSliding;

    public:
        Player();
        void handleEvent(SDL_Event &);
        void move(std::vector <Tile> &);
        void render(SDL_FRect &, Texture &);
        void setCamera(SDL_FRect &, int, int);
        void setBox(float, float) override;
        void updateBox() override;
};