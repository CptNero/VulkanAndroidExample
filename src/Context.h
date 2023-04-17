
#ifndef CONTEXT_H
#define CONTEXT_H

#include <android/asset_manager.h>

struct Context
{
    ANativeWindow* window = nullptr;
    AAssetManager* assetManager = nullptr;

    uint32_t windowWidth = 0;
    uint32_t windowHeight = 0;
};

#endif // CONTEXT_H
