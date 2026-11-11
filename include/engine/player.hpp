#pragma once
#include "entity.hpp"
#include "tile.hpp"
#include "animation.hpp"
#include "../other/const.hpp"
#include <vector>

class Player : public Entity
{
    private:
        SDL_FRect mFeetBox;
        SDL_FRect mCurrentFrame;
        SDL_FlipMode mFlipped;
        Animation mIdleAnimation;
        Animation mWalkingAnimation;
        Animation mRunningAnimation;
        Frame mAirFrame = {32, 0, kTileSize, kTileSize * 2};
        Frame mSlideFrame = {48, 0, kTileSize, kTileSize * 2};
        int mModifier;
        int mPushBack;
        bool mGrounded;
        bool mSliding;
        int mCoyoteTimer;
        int mJumpTimer;

        const int kJump = -200;
        const int kJumpBuffer = 6;
        const int kCoyote = 10;
        const int kGravity = 10;
        const int kMaxPull = 200;
        const int kSpeed = 100;

    public:
        Player();
        void handleEvent(SDL_Event &);
        void move(std::vector <Tile> &);
        void render(SDL_FRect &, Texture &);
        void setCamera(SDL_FRect &, int, int);
        void setPos(float, float) override;
        void setVel(float, float) override;
        void setBox(float, float) override;
        void updateBox() override;
        bool canJump();
};