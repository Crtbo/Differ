#pragma once
#include "scene.hpp"

class ExitScene : public Scene {
    private:
        static ExitScene sExitScene;

        ExitScene();

    public:
        static ExitScene *get();
        bool enter() override;
        bool exit() override;
        void handleEvent(SDL_Event &) override;
        void logic() override;
        void render() override;
};