#include "Engine.h"

#include <iostream>
#include <vector>

using namespace nu; //lets you take off the nu::

//Hi


int main()
{   
    //INITALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    //std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> v;

    for (int i = 0; i < 300; i++) {
        v.push_back(Vector2 { nu::RandomFloat(1920), nu::RandomFloat(1024) });
    }

    //MAIN LOOP
    bool quit = false;
    while (!quit) {
        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        //RENDER
        renderer.SetColorFloat(0, 0, 0);
        renderer.Clear();

        //Draw points
        for (int i = 0; i < v.size(); i++) {
            renderer.SetColorFloat(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            v[i] = v[i] + vel;
            renderer.DrawPoint(v[i].x, v[i].y);
        }

        //Draw rectangles
       /* for (int i = 0; i < 10; i++) {
            renderer.SetColor(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256));
            renderer.DrawFillRect(nu::RandomFloat(1920), nu::RandomFloat(1024), RandomInt(100), RandomInt(100));
        }*/

        //Draw lines
        /*for (int i = 0; i < 10; i++) {
            renderer.SetColorFloat(nu::RandomFloat(256), nu::RandomFloat(256), nu::RandomFloat(256));
            renderer.DrawLine(nu::RandomFloat(1920), nu::RandomFloat(1024), RandomInt(100), RandomInt(100));
        }*/

        renderer.Present();
    }
    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}


