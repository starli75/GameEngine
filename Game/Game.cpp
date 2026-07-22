#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>

using namespace nu; //lets you take off the nu::

void dosomething(std::vector<Vector2>& v) { //Refer to the already made vector instead of making another copy
    v[0].x = 40.0;
}



int main()
{   

    //TEXT ASSIGNMENT CODE
    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    //AUDIO ASSIGNMENT CODE
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("mario.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("scream.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    Color color;
    color.r = 1.0f;
    //INITALIZATION
    Engine::Get().Initialize();

    audio->update();


    
    Mesh meshPlayer{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{0.0f, 0.0f, 205.0f} };
    Mesh meshFlame{ {Vector2{-2,0}, Vector2{-3,1}, Vector2{-5,0}, Vector2{-3,-1}, Vector2{-2,0}}, Color{255.0f, 165.0f, 0.0f} };
    Mesh meshEnemy{ {Vector2{2, 0}, Vector2{-2, 2}, Vector2{-1,0}, Vector2{2,0}, Vector2{-2,-2}, Vector2{-1,0}}, Color{255.0f, 0.0f, 0.0f} };
    Model modelPlayer{ std::vector<Mesh> {meshPlayer, meshFlame} };
    Model modelEnemy{ std::vector<Mesh> {meshEnemy} };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = modelPlayer;
    playerDesc.transform = Transform{ Vector2{ 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 2000.0f;

    Player* player = new Player{ playerDesc };
    scene.AddActor(player);

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = modelEnemy;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), (float)nu::RandomFloat(Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f};
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


        //AUDIO
        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
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

        
        scene.Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }
    //SHUTDOWN
    

    return 0;
}


