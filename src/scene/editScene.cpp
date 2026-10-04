#include "../../include/scene/editScene.hpp"

bool EditScene::enter() {
    std::string path = "assets/maps/test.map";
    mMapWidth = 976;
    mMapHeight = 320;
    mTileTexture.loadFromFile("assets/images/tiles.png");
    setTiles(mTiles, mMapWidth, path);
    return true;
}
    
bool EditScene::exit() {
    saveTiles(mTiles, mMapWidth, "assets/maps/test.map");
    mTiles.clear();
    mTileTexture.destroy();
    return true;
}

void EditScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
		mCursor.x = event.motion.x;
		mCursor.y = event.motion.y;
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
    else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        placeTile(mTiles, mCursor, mCamera, mCurrentTileType);
}

void EditScene::logic() {
    if (mCursor.x < kScreenWidth / 4)
		mCamera.x -= kCursorVelocity;
	if (mCursor.x > kScreenWidth * 3 / 4)
		mCamera.x += kCursorVelocity;
	if (mCursor.y < kScreenHeight / 4)
		mCamera.y -= kCursorVelocity;
	if (mCursor.y > kScreenHeight * 3 / 4)
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
    
    mTileTexture.render(mCursor.x - mTileTexture.getWidth() / 2, mCursor.y - mTileTexture.getHeight() / 2);
}

EditScene::EditScene() {}

EditScene *EditScene::get() {
    return &sEditScene;
}

EditScene EditScene::sEditScene;