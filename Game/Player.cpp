#include "pch.h"

#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Model.h"
#include "Bullet.h"
#include "Assets.h"



void Player::Update(float dt)
{
    //Movement
    float thrust = 0.0f;


    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        
        thrust = m_speed;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;



    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1,0 }; 
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad)* thrust;
    SetVelocity(velocity * dt);

    //Fire
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
    {
        BulletDesc bulletDesc;
        bulletDesc.lifespan = 1.0f;
        bulletDesc.name = "Bullet";
        bulletDesc.tag = "PlayerBullet";
        bulletDesc.model = assets::bulletModel;
        bulletDesc.transform = m_transform;
        bulletDesc.speed = 2000.0f;


        Bullet* bullet = new Bullet{ bulletDesc };
        m_scene->AddActor(bullet);
    }

    Actor::Update(dt);

}
    void Player::OnCollision(Actor* other)
    {
        if (other->GetName() == "Enemy")
        {
            SetDestroyed();
        }
    }

