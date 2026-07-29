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

    SpaceGame game;
    game.Initialize();

    FMOD::System* audio;
    FMOD::System_Create(&audio);


    //INITALIZATION
    Engine::Get().Initialize();
    Engine::Get().GetAudio().Initialize();

    Font* font = new Font();
    font->Load("fonts/Blaster.ttf", 20);

    Text* text = new Text(font);
    text->Create(Engine::Get().GetRenderer(), "Hello World", Color{1.0f, 1.0f, 1.0f});

    Engine::Get().GetAudio().AddSound("Mario", "C:/Users/vvega/Desktop/Year 2/C++ Programming 2/Assignments/Game/Build/Assets/mario.mp3");

    audio->update();


    
   /* Mesh meshPlayer{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{0.0f, 0.0f, 205.0f} };
    Mesh meshFlame{ {Vector2{-2,0}, Vector2{-3,1}, Vector2{-5,0}, Vector2{-3,-1}, Vector2{-2,0}}, Color{255.0f, 165.0f, 0.0f} };
    Mesh meshEnemy{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{255.0f, 0.0f, 0.0f} };
    Model modelPlayer{ std::vector<Mesh> {meshPlayer, meshFlame} };
    Model modelEnemy{ std::vector<Mesh> {meshEnemy} };*/

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.damping = 1.0f;
    playerDesc.speed = 150000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = assets::enemyModel;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), (float)nu::RandomFloat(Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f};
        enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
        enemyDesc.speed = RandomFloat(1000.0f, 2000.0f);
        enemyDesc.damping = 3.0f;


        Enemy* enemy = new Enemy{ enemyDesc };
        scene.AddActor(enemy);
    }


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


        //AUDIO
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            Engine::Get().GetAudio().PlaySound("Mario");
        }
        
        //Engine::Get()
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();
        
        scene.Update(dt);

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
        text->Draw(Engine::Get().GetRenderer(), 40.0f, 40.0f);

        
        scene.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }
    //SHUTDOWN
    Engine::Get().Shutdown();
    Engine::Get().GetAudio().Shutdown();

    return 0;
}


