#include "../../include/scene/menuScene.hpp"
#include "../../include/scene/editScene.hpp"
#include "../../include/scene/exitScene.hpp"
#include "../../include/scene/levelScene.hpp"
#include "../../include/scene/settingsScene.hpp"
#include "../../include/other/global.hpp"

bool MenuScene::enter() {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    mPointerTexture.loadFromFile("assets/images/pointer.png");
    mCool1Texture.loadFromFile("assets/images/menu_1.png");
    mCool2Texture.loadFromFile("assets/images/menu_2.png");
    mCool3Texture.loadFromFile("assets/images/menu_3.png");
    mTextTitleTexture.loadFromRenderedText("Differ", textColor, gTitleFont);
    mTextStartTexture.loadFromRenderedText("Start level", textColor, gMainFont);
    mTextEditTexture.loadFromRenderedText("Edit level", textColor, gMainFont);
    mTextSettingsTexture.loadFromRenderedText("Settings", textColor, gMainFont);
    mTextExitTexture.loadFromRenderedText("Exit game", textColor, gMainFont);
    mTextCopyrightTexture.loadFromRenderedText("ChRT 2026 ©", textColor, gMainFont);
    mCurrentPoint = 0;
    return true;
}
    
bool MenuScene::exit() {
    mPointerTexture.destroy();
    mCool1Texture.destroy();
    mCool2Texture.destroy();
    mCool3Texture.destroy();
    mTextTitleTexture.destroy();
    mTextStartTexture.destroy();
    mTextEditTexture.destroy();
    mTextSettingsTexture.destroy();
    mTextExitTexture.destroy();
    mTextCopyrightTexture.destroy();
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        if (event.key.key == SDLK_RETURN)
            switch (mCurrentPoint) {
                case 0: setNextScene(LevelScene::get()); break;
                case 1: setNextScene(EditScene::get()); break;
                case 2: setNextScene(SettingsScene::get()); break;
                case 3: setNextScene(ExitScene::get());
            }
        if (event.key.key == SDLK_DOWN)
            mCurrentPoint = (mCurrentPoint + 1) % 4;
        if (event.key.key == SDLK_UP) {
            mCurrentPoint = mCurrentPoint - 1;
            if (mCurrentPoint < 0)
                mCurrentPoint = 3;
        }
    }
}

void MenuScene::logic() {}

void MenuScene::render() {
    mPointerTexture.render(kScreenWidth - 45, 100 + (mPointerTexture.getHeight() / 2) + (20 * mCurrentPoint));
    if (mCurrentPoint == 0) mCool1Texture.render(-60, 20, nullptr, SDL_FLIP_HORIZONTAL);
    if (mCurrentPoint == 1) mCool2Texture.render(20, 20);
    if (mCurrentPoint == 3) mCool3Texture.render(40, 0);
    mTextTitleTexture.render(kScreenWidth - 50 - mTextTitleTexture.getWidth(), 20);
    mTextStartTexture.render(kScreenWidth - 60 - mTextStartTexture.getWidth(), 100);
    mTextEditTexture.render(kScreenWidth - 60 - mTextEditTexture.getWidth(), 120);
    mTextSettingsTexture.render(kScreenWidth - 60 - mTextSettingsTexture.getWidth(), 140);
    mTextExitTexture.render(kScreenWidth - 60 - mTextExitTexture.getWidth(), 160);
    mTextCopyrightTexture.render((kScreenWidth - mTextCopyrightTexture.getWidth()) / 2, kScreenHeight - mTextCopyrightTexture.getHeight());
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;