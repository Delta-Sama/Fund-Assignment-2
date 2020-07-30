#include "Entity.h"
#include "Engine.h"

const float MAXVELOCITY = 3.0;

Entity::Entity(SDL_Rect s, SDL_FRect d, SDL_Texture* t) : GameObject(s, d, t)
{
	this->m_alive = true;
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

void Entity::SetBodyPosition()
{
	this->m_body.x = this->GetDstP()->x + (this->GetDstP()->w - this->m_body.w) / 2;
	this->m_body.y = this->GetDstP()->y + (this->GetDstP()->h - this->m_body.h) / 2;
}

void Entity::MovementUpdate()
{
	
}

void Entity::AddAnimator(Animator* animator)
{
	if (this->m_animator == nullptr)
		this->m_animator = animator;
	else
		delete animator;
}