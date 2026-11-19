#include "../../include/scene/settingsScene.hpp"
#include "../../include/scene/menuScene.hpp"
#include "../../include/other/const.hpp"
#include "../../include/other/global.hpp"

SettingsScene::SettingsScene() {}

SettingsScene *SettingsScene::get() {
    return &sSettingsScene;
}

bool SettingsScene::enter() {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    varText << kScreenWidth * gScale << 'x' << kScreenHeight * gScale;
    mFaceTexture.loadFromFile("assets/images/face.png");
    mCurrentTexture.loadFromFile("assets/images/pointer.png");
    mTextInfoTexture.loadFromRenderedText("Press UP or DOWN to change resolution", textColor, gMainFont);
    mTextResoultionTexture.loadFromRenderedText(varText.str().c_str(), textColor, gTitleFont);
    mFaceAnimation.setFrames(0, 0, 45, 67, 2, 20);
    return true;
}
    
bool SettingsScene::exit() {
    mFaceTexture.destroy();
    mCurrentTexture.destroy();
    mTextInfoTexture.destroy();
    mTextResoultionTexture.destroy();
    varText.str("");
    return true;
}

void SettingsScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        if (event.key.key == SDLK_BACKSPACE || event.key.key == SDLK_X)
            setNextScene(MenuScene::get());
        if (event.key.key == SDLK_UP && gScale < 4)
            gScale++;
        if (event.key.key == SDLK_DOWN && gScale > 1)
            gScale--;

        SDL_SetWindowSize(gWindow, kScreenWidth * gScale, kScreenHeight * gScale);
        varText.str("");
        varText << kScreenWidth * gScale << 'x' << kScreenHeight * gScale;
        SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
        mTextResoultionTexture.loadFromRenderedText(varText.str().c_str(), textColor, gTitleFont);
        varText.clear();
    }
}

void SettingsScene::logic() {
    mFaceAnimation.loop();
    mCurrentFrame = mFaceAnimation.getFrame();
}

void SettingsScene::render() {
    mFaceTexture.render((kScreenWidth - mFaceTexture.getWidth() / 2) / 2, kScreenHeight - mFaceTexture.getHeight() - 1, &mCurrentFrame);
    mTextInfoTexture.render((kScreenWidth - mTextInfoTexture.getWidth()) / 2, 60);
    mTextResoultionTexture.render((kScreenWidth - mTextResoultionTexture.getWidth()) / 2, 30);
}

SettingsScene SettingsScene::sSettingsScene;