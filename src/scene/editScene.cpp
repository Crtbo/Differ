#include "../../include/scene/editScene.hpp"
#include "../../include/scene/menuScene.hpp"
#include "../../include/other/global.hpp"

bool EditScene::enter() {
    std::string path = "assets/maps/test.map";
    mMapWidth = 61 * kTileSize;
    mMapHeight = 50 * kTileSize;
    mCurrentTileType = kTileAir;
    mPlacing = false;
    mNaked = false;
    mTileTexture.loadFromFile("assets/images/tiles.png");
    mCursorTexture.loadFromFile("assets/images/cursor.png");
    setTiles(mTiles, mMapWidth, mMapHeight, path);
    setTiles(mOverlay, mMapWidth, mMapHeight, "");
    mMainViewport.y = kViewportOffset;
    return true;
}
    
bool EditScene::exit() {
    saveTiles(mTiles, mMapWidth, "assets/maps/test.map");
    mTiles.clear();
    mOverlay.clear();
    mTileTexture.destroy();
    mCursorTexture.destroy();

    mMainViewport.y = 0;
    SDL_SetRenderViewport(gRenderer, &mMainViewport);
    return true;
}

void EditScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
		mCursor.x = event.motion.x / kScale; // DIVIDE BY SCREEN SCALE AMOUNT
		mCursor.y = event.motion.y / kScale;
    } else if (event.type == SDL_EVENT_MOUSE_WHEEL)
        if (event.wheel.y > 0) {
            mCurrentTileType--;
            if (mCurrentTileType < kTileAir)
                mCurrentTileType = kTileLand;        
        } else {
            mCurrentTileType++;
            if (mCurrentTileType > kTileLand)
                mCurrentTileType = kTileAir;    
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
    }
}

void EditScene::logic() {
    if (SDL_GetMouseFocus()) {
        if (mPlacing)
            placeTile(mTiles, mCursor, mCamera, mCurrentTileType);

        if (mCursor.x < kScreenWidth / 8)
            mCamera.x -= kCursorVelocity;
        if (mCursor.x > kScreenWidth * 7 / 8)
            mCamera.x += kCursorVelocity;
        if (mCursor.y < kScreenHeight / 8)
            mCamera.y -= kCursorVelocity;
        if (mCursor.y > kScreenHeight * 7 / 8)
            mCamera.y += kCursorVelocity;

        if (mCamera.x < 0)
            mCamera.x = 0;
        if (mCamera.y < 0)
            mCamera.y = 0;
        if (mCamera.x > mMapWidth - mCamera.w)
            mCamera.x = mMapWidth - mCamera.w;
        if (mCamera.y > mMapHeight - mCamera.h)
            mCamera.y = mMapHeight - mCamera.h;
    }
}

void EditScene::render() {
    SDL_SetRenderViewport(gRenderer, &mSideViewport);

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