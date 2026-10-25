#include <SDL3/SDL.h>
#include <vector>

struct Frame {
    SDL_FRect mSrc;  

    Frame(float x, float y, float w, float h) {
        mSrc.x = x;
        mSrc.y = y;
        mSrc.w = w;
        mSrc.h = h;
    }
};

struct Animation {
    std::vector <Frame> mFrames;
    int mCurrentFrame = 0;
    int mMaxFrames = 0;

    void setFrames(float x, float y, float w, float h, int numOfFrames) {
        mMaxFrames = numOfFrames;

        for (int i = 0; i < numOfFrames; i++)
            mFrames.push_back(Frame(x + (w * i), y, w, h));
    }

    SDL_FRect getFrame(int index) {
        return mFrames[index].mSrc;
    }

    SDL_FRect getFrame() {
        return mFrames[mCurrentFrame].mSrc;
    }

    void loop() {
        mCurrentFrame++;

        if (mCurrentFrame > mMaxFrames - 1)
            mCurrentFrame = 0;
    }
};