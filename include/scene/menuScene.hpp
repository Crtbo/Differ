#pragma once
#include "scene.hpp"
#include "../engine/player.hpp"
#include "../engine/texture.hpp"
#include "../engine/tile.hpp"
#include "../other/const.hpp"
#include <vector>

class MenuScene : public Scene {
    private:
        int mMapWidth, mMapHeight;
        Texture mPlayerTexture;
        Texture mTileTexture;
        Player player;
        std::vector <Tile> mTiles;
        SDL_FRect mCamera = {0, 0, kScreenWidth, kScreenHeight};
        static MenuScene sMenuScene;

        MenuScene();

    public:
        static MenuScene *get();
        bool enter() override;
        bool exit() override;
        void handleEvent(SDL_Event &) override;
        void logic() override;
        void render() override;
};