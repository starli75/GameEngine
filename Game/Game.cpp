#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>

using namespace nu; //lets you take off the nu::

void dosomething(std::vector<Vector2>& v) { //Refer to the already made vector instead of making another copy
    v[0].x = 40.0;
}

int main()
{   
    Color color;
    color.r = 1.0f;
    //INITALIZATION
    engine.Initialize();

    Mesh mesh{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{0.0f, 0.0f, 1.0f} };
    Player player{2000.0f, Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f }, std::vector<Mesh>{ mesh } };

    Vector2 position{ 960.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };


    //Photoshop
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
        
        //engine
        engine.Update();

        player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));
        player.Update(engine.GetTime().GetDeltaTime());

        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty())
            {
                points.push_back(engine.GetInput().GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - engine.GetInput().GetMousePosition();

                if (v.Length() > 10.0f) {
                    points.push_back(engine.GetInput().GetMousePosition());
                }
            }
        }

        //Undo
        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            points.pop_back();
        }

       /* velocity += (force * time.GetDeltaTime());
        position += (velocity * time.GetDeltaTime());

        position.x = math::Wrap(0.0f, 1920.0f, position.x);
        position.y = math::Wrap(0.0f, 1280.0f, position.y);*/

        //RENDER
        engine.GetRenderer().SetColorFloat(0, 0, 0);
        engine.GetRenderer().Clear();

        //Draw Line
        for (int i = 0; i < (int)points.size() - 1; i++) {
            engine.GetRenderer().SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //Rectangle in the middle
        player.Draw(engine.GetRenderer());
       /* renderer.SetColorFloat(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(position.x, position.y, 40, 40);*/

        engine.GetRenderer().Present();
    }
    //SHUTDOWN
    

    return 0;
}


