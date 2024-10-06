/**
 * @file main.cpp
 *
 * @brief Main function
 *
 */

#include "Application.h"

int main(void) {
    Application* app = new Application();
    if (!app->initialization()) {
        delete app;
        return EXIT_FAILURE;
    }

    // Create shaders and models
    app->createShaders();
    app->createModels();

    // Run the main loop
    app->run();

    // Cleanup
    delete app;
    return EXIT_SUCCESS;
}