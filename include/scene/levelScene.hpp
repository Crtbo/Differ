#pragma once
#include "scene.hpp"
#include "../engine/player.hpp"
#include "../engine/texture.hpp"
#include "../engine/tile.hpp"
#include "../other/const.hpp"
#include <vector>

class LevelScene : public Scene {
    private:
        int mMapWidth, mMapHeight;
        Texture mPlayerTexture;
        Texture mTileTexture;
        Texture mDebugTextTexture;
        Player player;
        std::vector <Tile> mTiles;
        SDL_FRect mCamera = {0, 0, kScreenWidth, kScreenHeight};
        static LevelScene sLevelScene;

        LevelScene();

    public:
        static LevelScene *get();
        bool enter() override;
        bool exit() override;
        void handleEvent(SDL_Event &) override;
        void logic() override;
        void render() override;
};