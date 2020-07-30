#include "Player.h"
#include "Engine.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

#include <algorithm>
#include <iostream>

#include "EventManager.h"

const float w = 128.0;
const float h = 128.0;

Player::Player()
	:Entity({0,0,128,128}, {0,0,w,h}, TEMA::GetTexture("player"))
{
	m_body = {0,0,74,122};
	this->SetBodyPosition();

	this->SetType(PLAYER);
	
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("run", 8, 1, 128, 0,0,512);
	this->GetAnimator()->AddAnimation("jump", 1, 2, 0, 0, 128*8, 512);
	this->GetAnimator()->AddAnimation("scroll", 4, 2, 128, 0, 0, 640);

	m_status = RUN;
	
	std::cout << "Player created\n";
}

Player::~Player()
{
	
}

void Player::update()
{
	if (SDL_NumJoysticks() < 1)
		this->KeyboardInput();
	else
		this->GamepadInput();

	m_animator->SetNextAnimation("run");

	if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		m_status = SCROLL;
		m_animator->SetNextAnimation("scroll");
	}
	else
	{
		if (m_status = SCROLL)
		{
			m_status = RUN;
		}
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) or m_status == JUMP)
	{
		m_animator->SetNextAnimation("jump");
		m_status = JUMP;
	}

	m_animator->Update();
	m_animator->PlayAnimation();
	
	MovementUpdate();
	
	this->SetBodyPosition();
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