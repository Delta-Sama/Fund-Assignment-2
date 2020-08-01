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
	m_body = {STARTX,FLOOR - 128,74,128};
	this->SetDstPosition();

	this->SetType(PLAYER);
	
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("run", 8, 1, 128, 0,0,512);
	this->GetAnimator()->AddAnimation("jump", 1, 2, 0, 0, 128 * 8, 512);
	this->GetAnimator()->AddAnimation("roll", 4, 2, 128, 0, 0, 640);
	this->GetAnimator()->AddAnimation("die", 5, 3, 128, 0, 128 * 4, 640);
	
	m_state = new EntityState(this);
	
	std::cout << "Player created\n";
}

Player::~Player()
{
	
}

void Player::update()
{
	m_state->Update();
	
	MovementUpdate();

	m_animator->Update();
	
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