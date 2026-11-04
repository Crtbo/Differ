#include "../../include/engine/player.hpp"
#include "../../include/other/detect.hpp"
#include "../../include/other/global.hpp"

Player::Player() {
    mModifier = 1;
    mGrounded = false;
    mSliding = false;
    mPushBack = 0;
    mCoyote = kTime;
    mIdleAnimation.setFrames(0, 0, kTileSize, kTileSize * 2, 2, 30);
    mWalkingAnimation.setFrames(0, 32, kTileSize, kTileSize * 2, 4, 10);
    mRunningAnimation.setFrames(0, 64, kTileSize, kTileSize * 2, 4, 7);
    mFlipped = SDL_FLIP_NONE;
}

void Player::handleEvent(SDL_Event &event) {
    const bool *keyStates = SDL_GetKeyboardState(nullptr);
    mModifier = keyStates[SDL_SCANCODE_LSHIFT] ? 2 : 1;
    if (!mPushBack) {
        if ((keyStates[SDL_SCANCODE_RIGHT] || keyStates[SDL_SCANCODE_D]) && (keyStates[SDL_SCANCODE_LEFT] || keyStates[SDL_SCANCODE_A]))
            mVel.x = 0;
        else if (keyStates[SDL_SCANCODE_LEFT] || keyStates[SDL_SCANCODE_A]) {
            mVel.x = -kSpeed;
            mFlipped = SDL_FLIP_NONE;
        } else if (keyStates[SDL_SCANCODE_RIGHT] || keyStates[SDL_SCANCODE_D]) {
            mVel.x = kSpeed;
            mFlipped = SDL_FLIP_HORIZONTAL;
        } else
            mVel.x = 0;
    }

    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_SPACE:
                if (mSliding && !mGrounded) {
                    mPushBack = kGravity;
                    mVel.x = keyStates[SDL_SCANCODE_LEFT] ? -kJump / 2 : kJump / 2;
                    mVel.y = kJump;
                } else if (mGrounded || mCoyote) {
                    mCoyote = 0;
                    mGrounded = false;
                    mVel.y = kJump;
                }
                
        }
    } else if (event.type == SDL_EVENT_KEY_UP && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_SPACE:
                if (!mGrounded && mVel.y <= 0)
                    mVel.y = -kGravity;
        }
    }
}

void Player::move(std::vector <Tile> &tiles) {
    int tileInd;
    mGrounded = false;
    mSliding = false;
    
    if (mCoyote > 0)
        mCoyote--;

    mPos.x += mVel.x * mModifier * gDeltaTime;
    updateBox();
    tileInd = checkSurface(mHitBox, tiles);
    if (tileInd != -1) {
        mSliding = true;
        mCoyote = kTime;
        if (tiles[tileInd].getBox().x < mHitBox.x)
            mPos.x = tiles[tileInd].getBox().x + tiles[tileInd].getBox().w;
        else
            mPos.x = tiles[tileInd].getBox().x - mHitBox.w;
        updateBox();
    }

    mPos.y += mVel.y * gDeltaTime;
    updateBox();
    tileInd = checkSurface(mHitBox, tiles);
    if (tileInd != -1) {
        mGrounded = true;
        mCoyote = kTime * 2;
        if (tiles[tileInd].getBox().y > mHitBox.y)
            mPos.y = tiles[tileInd].getBox().y - mHitBox.h;
        else {
            mPos.y = tiles[tileInd].getBox().y + tiles[tileInd].getBox().h;
            mVel.y = 0;   
        }
        updateBox();
    }
    
    mVel.y += kGravity;
    if (mVel.y >= kMaxPull && !mSliding) 
        mVel.y = kMaxPull;
    else if (mVel.y >= kMaxPull / 3 && mSliding)
        mVel.y = kMaxPull / 3;

    if (mPushBack) {
        mPushBack--;
        mVel.x = mVel.x > 0 ? mVel.x - kGravity : mVel.x + kGravity;
    }

    if (mVel.x != 0 && mModifier == 1) {
        mWalkingAnimation.loop();
        mCurrentFrame = mWalkingAnimation.getFrame();
    } else if (mVel.x != 0 && mModifier == 2) {
        mRunningAnimation.loop();
        mCurrentFrame = mRunningAnimation.getFrame();
    } else {
        mIdleAnimation.loop();
        mCurrentFrame = mIdleAnimation.getFrame();
    }  

    if (!mGrounded) mCurrentFrame = mAirFrame.mSrc;
    if (mSliding && !mGrounded) mCurrentFrame = mSlideFrame.mSrc;
}

void Player::render(SDL_FRect &camera, Texture &texture) {
    texture.render((int)mPos.x - camera.x, (int)mPos.y - camera.y, &mCurrentFrame, mFlipped);
    // SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0x00);
    // SDL_RenderRect(gRenderer, &mHitBox);
    // SDL_RenderRect(gRenderer, &mFeetBox);
}

void Player::setCamera(SDL_FRect &camera, int width, int height) {
    camera.x = (int)(mPos.x - (kScreenWidth - mHitBox.w) / 2);
	camera.y = (int)(mPos.y - (kScreenHeight - mHitBox.h) / 2);

    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x + camera.w > width)
        camera.x = width - camera.w;
    if (camera.y + camera.h > height)
        camera.y = height - camera.h;
}

void Player::setPos(float x, float y) {
    mPos.x = x;
    mPos.y = y;
    updateBox();
}

void Player::setVel(float x, float y) {
    mVel.x = x;
    mVel.y = y;
    updateBox();
}

void Player::setBox(float w, float h) {
    mHitBox.w = w / 4;
    mHitBox.h = h / 3;
    mFeetBox.w = w / 4;
    mFeetBox.h = 4;
    updateBox();
}

void Player::updateBox() {
    mHitBox.x = mPos.x;
    mHitBox.y = mPos.y;
    mFeetBox.x = mPos.x;
    mFeetBox.y = mPos.y + mHitBox.h - 4;
}