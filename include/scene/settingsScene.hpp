#pragma once
#include "scene.hpp"
#include "../engine/animation.hpp"
#include "../engine/texture.hpp"
#include <sstream>

class SettingsScene : public Scene {
    private:
        static SettingsScene sSettingsScene;
        Texture mFaceTexture;
        Texture mCurrentTexture;
        Texture mTextResoultionTexture;
        Animation mFaceAnimation;
        SDL_FRect mCurrentFrame;
        std::stringstream varText;

        SettingsScene();

    public:
        static SettingsScene *get();
        bool enter() override;
        bool exit() override;
        void handleEvent(SDL_Event &) override;
        void logic() override;
        void render() override;
};