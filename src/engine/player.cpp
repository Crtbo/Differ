#include "../../include/engine/player.hpp"
#include "../../include/other/detect.hpp"
#include "../../include/other/global.hpp"

Player::Player() {
    mGrounded = false;
    mSpeed = 2;
}

void Player::handleEvent(SDL_Event &event) {
    const bool *keyStates = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_A: mVel.x -= mSpeed; break;
            case SDLK_D: mVel.x += mSpeed; break;
            case SDLK_SPACE:
                if (mGrounded) {
                    mGrounded = false;
                    mVel.y = -10;
                }
        }
    } else if (event.type == SDL_EVENT_KEY_UP && event.key.repeat == 0) {
        switch (event.key.key) {
            case SDLK_A: mVel.x += mSpeed; break;
            case SDLK_D: mVel.x -= mSpeed; break;
        }
    }
}

void Player::move(std::vector <Tile> &tiles) {
    int tileInd;

    mPos.x += mVel.x;
    updateBox();
    tileInd = checkSurface(mHitBox, tiles);
    if (tileInd != -1) {
        if (tiles[tileInd].getBox().x < mHitBox.x)
            mPos.x = tiles[tileInd].getBox().x + tiles[tileInd].getBox().w;
        else
            mPos.x = tiles[tileInd].getBox().x - mHitBox.w;
        updateBox();
    }

    mPos.y += mVel.y;
    updateBox();
    tileInd = checkSurface(mFeetBox, tiles);
    if (tileInd != -1) {
        mGrounded = true;
        mPos.y = tiles[tileInd].getBox().y - mHitBox.h;
        updateBox();
    }

    mVel.y++;
    if (mVel.y >= 4) mVel.y = 4;
}

void Player::render(SDL_FRect &camera, Texture &texture) {
    texture.render((int)mPos.x - camera.x, (int)mPos.y - camera.y);
    // SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    // SDL_RenderRect(gRenderer, &mHitBox);
    // SDL_RenderRect(gRenderer, &mFeetBox);
}

void Player::setCamera(SDL_FRect &camera, int width, int height) {
    camera.x = static_cast<int>(mPos.x + mHitBox.w / 2 - kScreenWidth / 2);
    camera.y = static_cast<int>(mPos.y + mHitBox.h / 2 - kScreenHeight / 2);

    if (camera.x < 0)
        camera.x = 0;
    else if (camera.x + camera.w > width)
        camera.x = width - camera.w;
    if (camera.y < 0)
        camera.y = 0;
    else if (camera.y + camera.h > height)
        camera.y = height - camera.h;
}

void Player::setBox(float w, float h) {
    mHitBox.w = w;
    mHitBox.h = h;
    mFeetBox.w = w;
    mFeetBox.h = 4;
    updateBox();
}

void Player::updateBox() {
    mHitBox.x = mPos.x;
    mHitBox.y = mPos.y;
    mFeetBox.x = mPos.x;
    mFeetBox.y = mPos.y + mHitBox.h - 4;
}