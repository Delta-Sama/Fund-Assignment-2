#include "EntityState.h"
#include "Config.h"
#include "EventManager.h"

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

RunState::RunState(Player* player) : BehaviorState(player)
{

}

RunState::~RunState() {}

void RunState::Enter()
{

}

void RunState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("run");
	
	if (EVMA::KeyHeld(SDL_SCANCODE_S))
	{
		m_player->GetStateMachine()->ChangeState(new ScrollState(m_player));
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


//SCROLL:

ScrollState::ScrollState(Player* player) : BehaviorState(player)
{
	
}

ScrollState::~ScrollState() {}

void ScrollState::Enter()
{
	m_player->GetBody()->h /= 2;
	m_player->GetBody()->y = FLOOR - m_player->GetBody()->h;
}

void ScrollState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("scroll");
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

void ScrollState::Exit()
{
	m_player->GetBody()->h *= 2;
	m_player->GetBody()->y = FLOOR - m_player->GetBody()->h;
}

//JUMP:

JumpState::JumpState(Player* player) : BehaviorState(player)
{
	m_factor = 20;
	m_maxJumpProgress = m_factor * 2;
}

JumpState::~JumpState() {}

void JumpState::Enter()
{
	
}

void JumpState::Update()
{
	m_player->GetAnimator()->SetNextAnimation("jump");

	m_player->GetBody()->y = FLOOR - m_player->GetBody()->h - JUMPPOWER * (- pow((m_jumpProgress++ - m_factor), 2) + m_factor * m_factor);
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