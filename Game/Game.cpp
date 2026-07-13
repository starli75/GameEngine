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

    Actor player{ Transform{ Vector2 {640.0f, 512.0f}, 0.0f, 50.0f} };

    Vector2 position{ 960.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 800.0f;

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
            if (points.empty())
            {
                points.push_back(input.GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - input.GetMousePosition();

                if (v.Length() > 10.0f) {
                    points.push_back(input.GetMousePosition());
                }
            }
        }

        //Undo
        if (input.GetButtonPressed(Input::MouseButton::Right))
        {
            points.pop_back();
        }

        Vector2 force{ 0.0f, 0.0f };

        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

       /* velocity += (force * time.GetDeltaTime());
        position += (velocity * time.GetDeltaTime());

        position.x = math::Wrap(0.0f, 1920.0f, position.x);
        position.y = math::Wrap(0.0f, 1280.0f, position.y);*/

        //RENDER
        renderer.SetColorFloat(0, 0, 0);
        renderer.Clear();

        //Draw Line
        for (int i = 0; i < (int)points.size() - 1; i++) {
                renderer.SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
                renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //Rectangle in the middle
        player.Draw(renderer);
       /* renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x, position.y, 40, 40);*/

        renderer.Present();
    }
    //SHUTDOWN
    renderer.Shutdown();

    return 0;
}


