#include "Engine.h"

#include <iostream>
#include <vector>

using namespace nu; //lets you take off the nu::

void dosomething(std::vector<Vector2>& v) { //Refer to the already made vector instead of making another copy
    v[0].x = 40.0;
}

int main()
{   
    //INITALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    nu::Input input;
    input.Initialize();

    nu::Time time;

    Vector2 position{ 960.0f, 512.0f };
    float speed = 400.0f;
    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> points;

    //MAIN LOOP
    bool quit = false;
    while (!quit) {
        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        input.Update();

        time.Tick();

        if (input.GetButtonDown(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }

        Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = +speed;
        position += (velocity * time.GetDeltaTime());

        //RENDER
        renderer.SetColorFloat(0, 0, 0);
        renderer.Clear();

        //Draw points
        for (int i = 0; i < points.size(); i++) {
            renderer.SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x, position.y, 40, 40);

        renderer.Present();
    }
    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}


