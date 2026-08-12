#pragma once
#include <SDL3/SDL.h>

class Scene {
    public:
        virtual bool enter() = 0;
        virtual bool exit() = 0;
        virtual void handleEvent(SDL_Event &) = 0;
        virtual void logic() = 0;
        virtual void render() = 0;
        virtual ~Scene() = default;
};

void setNextScene(Scene *);

bool changeScene();

extern Scene *gCurrentScene;
extern Scene *gNextScene;