#include "../Engine/Engine.h"
#include "SDL3/SDL.h"

#include <iostream>

//Hi


int main()
{   
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);


    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }


        renderer.SetColor(0, 0, 0, 255);
        renderer.Clear();

        //Draw points
        for (int i = 0; i < 1000; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            renderer.DrawPoint(rand() % 1920, rand() % 1024);
        }

        //Draw rectangles
        for (int i = 0; i < 10; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawFillRect(rand() % 1920, rand() % 1024, rand() % 100, rand() % 100);
        }

        //Draw lines
        for (int i = 0; i < 10; i++) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawLine(rand() % 1920, rand() % 1024, rand() % 100, rand() % 100);
        }

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}


