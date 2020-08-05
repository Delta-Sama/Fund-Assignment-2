#include "EntityState.h"
#include "Config.h"
#include "Engine.h"
#include "EventManager.h"
#include "SoundManager.h"

BehaviorState::BehaviorState(Player* player) : m_player(player)
{
	
}

BehaviorState::~BehaviorState() {}

EntityState::EntityState(Player* player) : m_player(player)
{
	ChangeState(new RunState(m_player));
}

EntityState::~EntityState()
{
	
}

void EntityState::Update()
{
	if (m_state)
	{
		m_state->Update();
	}
}

void EntityState::ChangeState(BehaviorState* newState)
{
	if (m_state)
	{
		m_state->Exit();
		delete m_state;
	}
	m_state = newState;
	m_state->Enter();
}

//States:

// RUN:

RunState::RunState(Player* player) : BehaviorState(player) {}

RunState::~RunState() {}

void RunState::Enter()
{

}

void RunState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("run");

	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		m_player->SetAccelX(-1.0f);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		m_player->SetAccelX(1.0f);
	}
	if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		m_player->GetStateMachine()->ChangeState(new RollState(m_player));
		return;
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
	{
		m_player->GetStateMachine()->ChangeState(new JumpState(m_player));
		return;
	}
}

void RunState::Exit()
{

}


//Roll:

RollState::RollState(Player* player) : BehaviorState(player)
{
	
}

RollState::~RollState() {}

void RollState::Enter()
{
	m_player->GetBody()->h /= 2;
	m_player->GetBody()->y = FLOOR - m_player->GetBody()->h;
}

void RollState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("roll");
	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		m_player->SetAccelX(-1.0f);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		m_player->SetAccelX(1.0f);
	}
	if (not EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		m_player->GetStateMachine()->ChangeState(new RunState(m_player));
		return;
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
	{
		m_player->GetStateMachine()->ChangeState(new JumpState(m_player));
		return;
	}
}

void RollState::Exit()
{
	m_player->GetBody()->h *= 2;
	m_player->GetBody()->y = FLOOR - m_player->GetBody()->h;
}

//JUMP:

JumpState::JumpState(Player* player) : BehaviorState(player) {}

JumpState::~JumpState() {}

void JumpState::Enter()
{
	m_factor = 20;
	m_maxJumpProgress = m_factor * 2;
	SOMA::PlaySound("jump", 0, 1);
}

void JumpState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("jump");

	m_player->GetBody()->y = FLOOR - m_player->GetBody()->h - JUMPPOWER * (- pow((m_jumpProgress++ - m_factor), 2) + m_factor * m_factor);

	if (EVMA::KeyHeld(SDL_SCANCODE_A))
	{
		m_player->SetAccelX(-1.0f);
	}
	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
	{
		m_player->SetAccelX(1.0f);
	}
	if (m_jumpProgress > m_maxJumpProgress)
	{
		m_player->GetBody()->y = FLOOR - m_player->GetBody()->h;
		m_player->GetStateMachine()->ChangeState(new RunState(m_player));
		return;
	}
}

void JumpState::Exit()
{
	
}

DeathState::DeathState(Player* player) : BehaviorState(player) {}

DeathState::~DeathState() {}

void DeathState::Enter()
{
	Animation* dieAnim = m_player->GetAnimator()->GetAnimation("die");
	m_diedAnim = dieAnim->GetFramesFrequency()/10 * dieAnim->GetMaxFrames() + FPS * 2;
	m_player->GetAnimator()->PlayFullAnimation("die");
	m_player->SetStatus(DYING);
	SOMA::PlaySound("death", 0, 2);
}

void DeathState::Update()
{
	//std::cout << "Die update :" << m_diedAnim << "\n";
	if (m_diedAnim-- <= 0)
	{
		m_player->SetStatus(DIED);
		m_player->SetAlive(false);
		return;
	}

}

void DeathState::Exit()
{
	
}
