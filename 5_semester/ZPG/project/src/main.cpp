#include "Application.h"

int main() {
    Application* app = new Application();
    app->initialization();
    app->createShaders();
    app->createModels();
    app->run();
    delete app;
    return 0;
}
