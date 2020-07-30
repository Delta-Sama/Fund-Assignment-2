#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Config.h"
#include "EventManager.h"

#include <algorithm>
#include <iostream>

const float w = 128.0;
const float h = 128.0;

Player::Player()
	:Entity({0,0,128,128}, {0,0,w,h}, TEMA::GetTexture("player"))
{
	m_body = {STARTX,FLOOR - 122,74,122};
	this->SetDstPosition();

	this->SetType(PLAYER);
	
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("run", 8, 1, 128, 0,0,512);
	this->GetAnimator()->AddAnimation("jump", 1, 2, 0, 0, 128*8, 512);
	this->GetAnimator()->AddAnimation("scroll", 4, 2, 128, 0, 0, 640);

	m_state = new EntityState(this);
	
	std::cout << "Player created\n";
}

Player::~Player()
{
	
}

void Player::update()
{
	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		this->SetAccelX(-1.0f);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		this->SetAccelX(1.0f);
	}
	
	MovementUpdate();
	
	m_state->Update();

	m_animator->Update();
	m_animator->PlayAnimation();
	
	this->SetDstPosition();
}

void Player::clean()
{
	
}

void Player::KeyboardInput()
{
	
}

void Player::GamepadInput()
{
	
}