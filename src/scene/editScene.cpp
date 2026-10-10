#include "../../include/scene/editScene.hpp"

bool EditScene::enter() {
    std::string path = "assets/maps/test.map";
    mMapWidth = 61 * kTileWidth;
    mMapHeight = 50 * kTileHeight;
    mCurrentTileType = kTileAir;
    mPlacing = false;
    mTileTexture.loadFromFile("assets/images/tiles.png");
    mCursorTexture.loadFromFile("assets/images/cursor.png");
    setTiles(mTiles, mMapWidth, mMapHeight, path);
    setTiles(mOverlay, mMapWidth, mMapHeight, "");
    return true;
}
    
bool EditScene::exit() {
    saveTiles(mTiles, mMapWidth, "assets/maps/test.map");
    mTiles.clear();
    mOverlay.clear();
    mTileTexture.destroy();
    mCursorTexture.destroy();
    return true;
}

void EditScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
		mCursor.x = event.motion.x / kScale; // DIVIDE BY SCREEN SCALE AMOUNT
		mCursor.y = event.motion.y / kScale;
    } else if (event.type == SDL_EVENT_MOUSE_WHEEL )
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
}

void EditScene::logic() {
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

void EditScene::render() {
    for (int i = 0; i < mTiles.size(); i++)
        mTiles[i].render(mCamera, mTileTexture);

    for (int i = 0; i < mOverlay.size(); i++)
        mOverlay[i].render(mCamera, mTileTexture);
    
    mCursorTexture.render(mCursor.x - mCursorTexture.getWidth() / 2, mCursor.y - mCursorTexture.getHeight() / 2);
}

EditScene::EditScene() {}

EditScene *EditScene::get() {
    return &sEditScene;
}

EditScene EditScene::sEditScene;