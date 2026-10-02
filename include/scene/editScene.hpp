#pragma once
#include "scene.hpp"

class EditScene : public Scene {
    private:
        static EditScene sEditScene;

        EditScene();

    public:
        static EditScene *get();
        bool enter() override;
        bool exit() override;
        void handleEvent(SDL_Event &) override;
        void logic() override;
        void render() override;
};