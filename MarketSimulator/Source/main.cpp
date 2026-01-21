#include <iostream>

#include "app.h"


int main()
{
    App* app = new App();
    
    app->Init();

    app->Update();
}