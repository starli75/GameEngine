#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "Font.h"
#include "Text.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>

using namespace nu; //lets you take off the nu::

void dosomething(std::vector<Vector2>& v) { //Refer to the already made vector instead of making another copy
    v[0].x = 40.0;
}



int main()
{ 
    SetWorkingDirectory("Assets");


    //INITALIZATION
    Engine::Get().Initialize();
    Engine::Get().GetAudio().Initialize();

    SpaceGame game;
    game.Initialize();

    FMOD::System* audio;
    FMOD::System_Create(&audio);

    Engine::Get().GetAudio().PlaySound("AsteroidTitle");


    //Photoshop
    std::vector<Vector2> points;

    //MAIN LOOP
    bool quit = false;
    while (!quit) {
        //UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            Engine::Get().GetAudio().Update();
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        
        //Engine::Get()
        Engine::Get().Update();


        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left)) {
            if (points.empty())
            {
                points.push_back(Engine::Get().GetInput().GetMousePosition());
            }
            else
            {
                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePosition();

                if (v.Length() > 10.0f) {
                    points.push_back(Engine::Get().GetInput().GetMousePosition());
                }
            }
        }

        //Undo
        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Right))
        {
            points.pop_back();
        }


        //RENDER
        Engine::Get().GetRenderer().SetColorFloat(0, 0, 0);
        Engine::Get().GetRenderer().Clear();

        //Draw Line
        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        //Draw text
       
        game.Draw(Engine::Get().GetRenderer());
        
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }
    //SHUTDOWN
    Engine::Get().Shutdown();
    Engine::Get().GetAudio().Shutdown();

    return 0;
}


