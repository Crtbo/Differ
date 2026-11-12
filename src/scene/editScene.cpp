#include "../../include/scene/editScene.hpp"
#include "../../include/scene/menuScene.hpp"
#include "../../include/other/global.hpp"

bool EditScene::enter() {
    std::string path = "assets/maps/test.map";
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    mTileTexture.loadFromFile("assets/images/tiles.png");
    mCursorTexture.loadFromFile("assets/images/cursor.png");
    mInfoTextTexture.loadFromRenderedText(" - CURRENT TILE (scroll to change)", textColor, gMainFont);
    mMapWidth = 61 * kTileSize;
    mMapHeight = 50 * kTileSize;
    mCurrentTileType = kTileAir;
    mPlacing = false;
    mNaked = false;
    setTiles(mTiles, mMapWidth, mMapHeight, path);
    setTiles(mOverlay, mMapWidth, mMapHeight, "");
    mMainViewport.y = kViewportOffset;
    mCameraVel = {0, 0};
    return true;
}
    
bool EditScene::exit() {
    saveTiles(mTiles, mMapWidth, "assets/maps/test.map");
    mTiles.clear();
    mOverlay.clear();
    mTileTexture.destroy();
    mCursorTexture.destroy();
    mInfoTextTexture.destroy();

    mMainViewport.y = 0;
    SDL_SetRenderViewport(gRenderer, &mMainViewport);
    return true;
}

void EditScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
		mCursor.x = event.motion.x / gScale; // DIVIDE BY SCREEN SCALE AMOUNT
		mCursor.y = event.motion.y / gScale - kViewportOffset;
    } else if (event.type == SDL_EVENT_MOUSE_WHEEL)
        if (event.wheel.y > 0) {
            mCurrentTileType--;
            if (mCurrentTileType < 1)
                mCurrentTileType = kTotalTileSprites - 1;        
        } else {
            mCurrentTileType++;
            if (mCurrentTileType > kTotalTileSprites - 1)
                mCurrentTileType = 1;    
        }
    
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
        mPlacing = true; 
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT)
        mPlacing = false;
    
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        if (event.key.key == SDLK_BACKSPACE)
            setNextScene(MenuScene::get());
        if (event.key.key == SDLK_SPACE)
            mNaked = !mNaked;
        if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
            mCameraVel.x -= kCursorVel;
        if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
            mCameraVel.x += kCursorVel;
        if (event.key.key == SDLK_UP || event.key.key == SDLK_W)
            mCameraVel.y -= kCursorVel;
        if (event.key.key == SDLK_DOWN || event.key.key == SDLK_S)
            mCameraVel.y += kCursorVel;
    }  else if (event.type == SDL_EVENT_KEY_UP && event.key.repeat == 0) {
        if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
            mCameraVel.x += kCursorVel;
        if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
            mCameraVel.x -= kCursorVel;
        if (event.key.key == SDLK_UP || event.key.key == SDLK_W)
            mCameraVel.y += kCursorVel;
        if (event.key.key == SDLK_DOWN || event.key.key == SDLK_S)
            mCameraVel.y -= kCursorVel;
    }
}

void EditScene::logic() {
    if (SDL_GetMouseFocus()) {
        if (mPlacing)
            placeTile(mTiles, mCursor, mCamera, mCurrentTileType);

        if (mCursor.x < kScreenWidth / 8)
            mCamera.x -= kCursorVel;
        if (mCursor.x > kScreenWidth * 7 / 8)
            mCamera.x += kCursorVel;
        if (mCursor.y < kScreenHeight / 8)
            mCamera.y -= kCursorVel;
        if (mCursor.y > kScreenHeight * 7 / 8 - kViewportOffset)
            mCamera.y += kCursorVel;
    }

    mCamera.x += mCameraVel.x;
    mCamera.y += mCameraVel.y;

    if (mCamera.x < 0)
        mCamera.x = 0;
    if (mCamera.y < 0)
        mCamera.y = 0;
    if (mCamera.x > mMapWidth - mCamera.w)
        mCamera.x = mMapWidth - mCamera.w;
    if (mCamera.y > mMapHeight - mCamera.h + kViewportOffset)
        mCamera.y = mMapHeight - mCamera.h + kViewportOffset;
}

void EditScene::render() {
    SDL_SetRenderViewport(gRenderer, &mSideViewport);
    mInfoTextTexture.render(16, 0);
    mTileTexture.render(0, 0, &gTileClips[mCurrentTileType]);

    if (SDL_GetMouseFocus()) // This is not good (two cursors for both viewports)
        mCursorTexture.render(mCursor.x - mCursorTexture.getWidth() / 2, mCursor.y - mCursorTexture.getHeight() / 2 + kViewportOffset);

    SDL_SetRenderViewport(gRenderer, &mMainViewport);
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);

    if (!mNaked)
        for (int i = 0; i < mOverlay.size(); i++)
            mOverlay[i].render(mCamera, mTileTexture);
    
    if (SDL_GetMouseFocus())
        mCursorTexture.render(mCursor.x - mCursorTexture.getWidth() / 2, mCursor.y - mCursorTexture.getHeight() / 2);
}

EditScene::EditScene() {}

EditScene *EditScene::get() {
    return &sEditScene;
}

EditScene EditScene::sEditScene;