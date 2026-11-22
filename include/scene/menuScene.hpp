#pragma once
#include "scene.hpp"
#include "../engine/animation.hpp"
#include "../engine/texture.hpp"

class MenuScene : public Scene {
    private:
        int mCurrentPoint;
        const int kBgWidth = 237, kBgHeight = 216;
        Texture mBackGroundTexture;
        Texture mAnimTexture;
        Texture mPointerTexture;
        Texture mCool1Texture;
        Texture mCool2Texture;
        Texture mCool3Texture;
        Texture mCool4Texture;
        Texture mTextTitleTexture;
        Texture mTextStartTexture;
        Texture mTextEditTexture;
        Texture mTextSettingsTexture;
        Texture mTextExitTexture;
        Texture mTextCopyrightTexture;
        Animation mAnim1;
        SDL_FRect mCurrentBg;
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