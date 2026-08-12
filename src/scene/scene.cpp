#include "../../include/scene/scene.hpp"
#include "../../include/scene/ExitScene.hpp"

void setNextScene(Scene *newScene) {
    if (gNextScene != ExitScene::get())
        gNextScene = newScene;
}

bool changeScene() {
    bool success = true;

    if (gNextScene != nullptr)
    {
        success = gCurrentScene->exit() && success;
        success = gNextScene->enter() && success;

        gCurrentScene = gNextScene;
        gNextScene = nullptr;
    }

    return success;
}

Scene *gCurrentScene = nullptr;
Scene *gNextScene = nullptr;