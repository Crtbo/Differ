#pragma once
#include "scene.hpp"
#include "../engine/texture.hpp"

class MenuScene : public Scene {
    private:
        int mCurrentPoint;
        Texture mPointerTexture;
        Texture mCool1Texture;
        Texture mCool2Texture;
        Texture mCool3Texture;
        Texture mTextTitleTexture;
        Texture mTextStartTexture;
        Texture mTextEditTexture;
        Texture mTextExitTexture;
        Texture mTextCopyrightTexture;
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