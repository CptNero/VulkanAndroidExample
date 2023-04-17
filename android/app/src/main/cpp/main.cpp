#include "ExampleRenderer.h"
#include "Context.h"
#include "android_native_app_glue.h"

namespace {

extern "C" {

void HandleCommand(android_app* app, int32_t cmd)
{
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            if (!app->userData) {
                Context context = {};
                context.window = app->window;
                context.windowWidth = ANativeWindow_getWidth(app->window);
                context.windowHeight = ANativeWindow_getHeight(app->window);
                context.assetManager = app->activity->assetManager;

                app->userData = new ExampleRenderer(context);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            if (app->userData) {
                auto* renderer = reinterpret_cast<ExampleRenderer*>(app->userData);
                delete renderer;
                app->userData = nullptr;
            }
            break;
    }
}

void android_main(struct android_app* app)
{
    app->onAppCmd = HandleCommand;
    app->userData = nullptr;

    ANativeActivity* activity = app->activity;

    int events = 0;
    android_poll_source* source = nullptr;

    while (true) {
        int ident;

        while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&source)) >= 0) {
            if (source) {
                source->process(app, source);
            }

            if (app->destroyRequested) {
                return;
            }
        }

        if (app->userData) {
            auto* renderer = reinterpret_cast<ExampleRenderer*>(app->userData);
            renderer->drawFrame();
        }
    }

    ANativeActivity_finish(app->activity);
}

} // extern "C"

}
