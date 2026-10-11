#pragma once
#include "scene.hpp"
#include "../engine/texture.hpp"
#include "../engine/tile.hpp"
#include "../other/const.hpp"
#include <vector>

class EditScene : public Scene {
    private:
        const int kCursorVelocity = 2;
        int mMapWidth, mMapHeight;
        int mCurrentTileType;
        bool mPlacing, mNaked;
        Texture mTileTexture;
        Texture mCursorTexture;
        std::vector <Tile> mTiles;
        std::vector <Tile> mOverlay;
        SDL_FRect mCamera = {0, 0, kScreenWidth, kScreenHeight};
        SDL_Point mCursor = {kScreenWidth / 2, kScreenHeight / 2};
        static EditScene sEditScene;

        EditScene();

    public:
        static EditScene *get();
        bool enter() override;
        bool exit() override;
        void handleEvent(SDL_Event &) override;
        void logic() override;
        void render() override;
};