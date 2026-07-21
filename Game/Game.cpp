#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

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



    Mesh meshOne{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{0.0f, 0.0f, 205.0f} };
    Mesh meshFlame{ {Vector2{-2,0}, Vector2{-3,1}, Vector2{-5,0}, Vector2{-3,-1}, Vector2{-2,0}}, Color{255.0f, 165.0f, 0.0f} };
    Mesh meshTwo{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{255.0f, 0.0f, 0.0f} };
    Model modelOne{ std::vector<Mesh> {meshOne, meshFlame} };
    Model modelTwo{ std::vector<Mesh> {meshTwo} };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = modelOne;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = modelTwo;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)engine.GetRenderer().GetWidth()), (float)nu::RandomFloat(engine.GetRenderer().GetHeight())}, 90.0f, 10.0f };
        enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
        enemyDesc.speed = 2000.0f;


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
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        
        //engine
        engine.Update();

        float dt = engine.GetTime().GetDeltaTime();
        
        scene.Update(dt);

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


        //RENDER
        engine.GetRenderer().SetColorFloat(0, 0, 0);
        engine.GetRenderer().Clear();

        //Draw Line
        for (int i = 0; i < (int)points.size() - 1; i++) {
            engine.GetRenderer().SetColorFloat(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        
        scene.Draw(engine.GetRenderer());

        engine.GetRenderer().Present();
    }
    //SHUTDOWN
    

    return 0;
}


