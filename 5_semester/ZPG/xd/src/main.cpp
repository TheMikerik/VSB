#include "Core/Application.h"

int main()
{   
    Application App;
    App.initialization();
    App.createScenes();
    App.run();
    return 0;
}