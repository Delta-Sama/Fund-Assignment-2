#include "Entity.h"

#include <algorithm>

#include "Engine.h"

const float MAXVELOCITY = 6.0;

Entity::Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : GameObject(s, d, t)
{
	this->m_alive = true;
	this->m_maxVelocity = MAXVELOCITY;
	this->m_drag = 0.88;
	this->m_status = ALIVE;
}

Entity::~Entity()
{
	if (this->m_animator != nullptr)
	{
		this->m_animator->Clean();
		delete this->m_animator;
		this->AddAnimator(nullptr);
	}
}

void Entity::SetDstPosition()
{
	this->GetDstP()->x = this->m_body.x - (this->GetDstP()->w - this->m_body.w) / 2;
	this->GetDstP()->y = this->m_body.y - (this->GetDstP()->h - this->m_body.h);
}

void Entity::StopX() { m_velocity.x = 0.0; }

void Entity::SetAccelX(float a) { m_accel.x = a; }
float Entity::GetVelX() { return m_velocity.x; }

void Entity::MovementUpdate()
{
	m_velocity.x += m_accel.x;
	m_velocity.x *= m_drag;
	m_velocity.x = std::min(std::max(m_velocity.x, -m_maxVelocity), (m_maxVelocity));
	
	m_body.x += (int)this->m_velocity.x;

	m_accel.x = 0.0;

	static int x = 0, y = 0;
	if (x == 0 or y == 0)
		SDL_GetWindowSize(Engine::Instance().GetWindow(), &x, &y);

	if (m_body.x < 0)
	{
		m_body.x = 0;
	}
	else if (m_body.x > x - m_body.w)
	{
		m_body.x = x - m_body.w;
	}
}

void Entity::AddAnimator(Animator* animator)
{
	if (this->m_animator == nullptr)
		this->m_animator = animator;
	else
		delete animator;
}