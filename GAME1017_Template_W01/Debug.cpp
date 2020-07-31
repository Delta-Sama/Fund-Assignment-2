#include "Debug.h"
#include "ScrollingManager.h"
#include "Util.h"

DebugMode::DebugMode(GameState* scene)
{
	m_playScene = scene;
}

void DebugMode::Draw()
{
	if (m_mode)
	{
		Player* player = m_playScene->GetPlayer();
		SDL_FRect* plrtemp = player->GetBody();
		Util::DrawRect({ plrtemp->x, plrtemp->y }, plrtemp->w, plrtemp->h);
		SDL_FRect* plrdst = player->GetDstP();
		Util::DrawRect({ plrdst->x, plrdst->y }, plrdst->w, plrdst->h, {1,1,0,1});
		
		for (Obstacle* obst : *SCMA::GetObstacles())
		{
			SDL_FRect* temp = obst->GetDstP();
			Util::DrawRect({ temp->x, temp->y }, temp->w, temp->h, {1,0,0,1});
		}
	}
}