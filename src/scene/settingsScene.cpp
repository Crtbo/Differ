#include "../../include/scene/settingsScene.hpp"
#include "../../include/scene/menuScene.hpp"
#include "../../include/other/const.hpp"
#include "../../include/other/global.hpp"

SettingsScene::SettingsScene() {}

SettingsScene *SettingsScene::get() {
    return &sSettingsScene;
}

bool SettingsScene::enter() {
    mFaceTexture.loadFromFile("assets/images/face.png");
    mFaceAnimation.setFrames(0, 0, 45, 67, 2, 20);
    return true;
}
    
bool SettingsScene::exit() {
    mFaceTexture.destroy();
    return true;
}

void SettingsScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0)
        if (event.key.key == SDLK_BACKSPACE)
            setNextScene(MenuScene::get());
}

void SettingsScene::logic() {
    mFaceAnimation.loop();
    mCurrentFrame = mFaceAnimation.getFrame();
}

void SettingsScene::render() {
    mFaceTexture.render((kScreenWidth - mFaceTexture.getWidth() / 2) / 2, (kScreenHeight - mFaceTexture.getHeight()) / 2, &mCurrentFrame);
}

SettingsScene SettingsScene::sSettingsScene;