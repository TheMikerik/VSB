#include "Application.h"

int main() {
    Application* app = new Application();
    app->initialization();
    app->createScenes();
    app->run();
    delete app;
    return 0;
}
