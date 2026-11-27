#include "../../include/scene/menuScene.hpp"
#include "../../include/scene/editScene.hpp"
#include "../../include/scene/exitScene.hpp"
#include "../../include/scene/levelScene.hpp"
#include "../../include/scene/settingsScene.hpp"
#include "../../include/other/global.hpp"

bool MenuScene::enter() {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    mBackGroundTexture.loadFromFile("assets/images/bg_1.png");
    mAnimTexture.loadFromFile("assets/images/misc_anim.png");
    mTitleTexture.loadFromFile("assets/images/title.png");
    mPointerTexture.loadFromFile("assets/images/pointer.png");
    mCool1Texture.loadFromFile("assets/images/menu_1.png");
    mCool2Texture.loadFromFile("assets/images/menu_2.png");
    mCool3Texture.loadFromFile("assets/images/menu_3.png");
    mCool4Texture.loadFromFile("assets/images/menu_4.png");
    mTextStartTexture.loadFromRenderedText("Start level", textColor, gMainFont);
    mTextEditTexture.loadFromRenderedText("Edit level", textColor, gMainFont);
    mTextSettingsTexture.loadFromRenderedText("Settings", textColor, gMainFont);
    mTextExitTexture.loadFromRenderedText("Exit game", textColor, gMainFont);
    mTextCopyrightTexture.loadFromRenderedText("ChRT 2026 ©", textColor, gMainFont);
    mAnim1.setFrames(0, 0, 4, kBgHeight, 4, 2);
    mCurrentPoint = 0;
    mCurrentBg = {(float)kBgWidth, 0, (float)kBgWidth, (float)kBgHeight};
    return true;
}
    
bool MenuScene::exit() {
    mBackGroundTexture.destroy();
    mAnimTexture.destroy();
    mTitleTexture.destroy();
    mPointerTexture.destroy();
    mCool1Texture.destroy();
    mCool2Texture.destroy();
    mCool3Texture.destroy();
    mCool4Texture.destroy();
    mTextStartTexture.destroy();
    mTextEditTexture.destroy();
    mTextSettingsTexture.destroy();
    mTextExitTexture.destroy();
    mTextCopyrightTexture.destroy();
    return true;
}

void MenuScene::handleEvent(SDL_Event &event) {
    if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
        if (event.key.key == SDLK_RETURN || event.key.key == SDLK_Z || event.key.key == SDLK_Y)
            switch (mCurrentPoint) {
                case 0: setNextScene(LevelScene::get()); break;
                case 1: setNextScene(EditScene::get()); break;
                case 2: setNextScene(SettingsScene::get()); break;
                case 3: setNextScene(ExitScene::get());
            }
        if (event.key.key == SDLK_DOWN || event.key.key == SDLK_S)
            mCurrentPoint = (mCurrentPoint + 1) % 4;
        if (event.key.key == SDLK_UP || event.key.key == SDLK_W) {
            mCurrentPoint = mCurrentPoint - 1;
            if (mCurrentPoint < 0)
                mCurrentPoint = 3;
        }

        switch (mCurrentPoint) {
            case 0: mCurrentBg.x = kBgWidth; mCurrentBg.y = 0; break;
            case 1: mCurrentBg.x = 0; mCurrentBg.y = kBgHeight; break;
            case 2: mCurrentBg.x = kBgWidth; mCurrentBg.y = kBgHeight; break;
            case 3: mCurrentBg.x = 0; mCurrentBg.y = 0; break;
        }
    }
}

void MenuScene::logic() {
    mAnim1.loop();
}

void MenuScene::render() {
    SDL_FRect frame = mAnim1.getFrame();
    mBackGroundTexture.render(0, 0, &mCurrentBg);
    mAnimTexture.render(kBgWidth - 8, 0, &frame);
    mTitleTexture.render(kBgWidth + ((kScreenWidth - kBgWidth) - mTitleTexture.getWidth()) / 2, 30);
    if (mCurrentPoint == 0) mCool1Texture.render(-80, 20, nullptr, SDL_FLIP_HORIZONTAL);
    if (mCurrentPoint == 1) mCool2Texture.render(20, 20);
    if (mCurrentPoint == 2) mCool3Texture.render(40, 0);
    if (mCurrentPoint == 3) mCool4Texture.render(40, 0);
    mTextStartTexture.render(kScreenWidth - 40 - mTextStartTexture.getWidth(), 100);
    mTextEditTexture.render(kScreenWidth - 40 - mTextEditTexture.getWidth(), 120);
    mTextSettingsTexture.render(kScreenWidth - 40 - mTextSettingsTexture.getWidth(), 140);
    mTextExitTexture.render(kScreenWidth - 40 - mTextExitTexture.getWidth(), 160);
    mTextCopyrightTexture.render(kScreenWidth - 40 - mTextCopyrightTexture.getWidth(), kScreenHeight - mTextCopyrightTexture.getHeight());
}

MenuScene::MenuScene() {}

MenuScene *MenuScene::get() {
    return &sMenuScene;
}

MenuScene MenuScene::sMenuScene;