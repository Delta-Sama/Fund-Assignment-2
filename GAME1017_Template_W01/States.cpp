#include "States.h"

#include "CollisionManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "GameObjectManager.h"
#include "Level1.h"
#include "StateManager.h"
#include "UIManager.h"

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#include "ScrollingManager.h"

void print(std::string msg)
{
	std::cout << msg << "\n";
}

// Begin State. CTRL+M+H and CTRL+M+U to turn on/off collapsed code.
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}
void State::Resume() {}
// End State.

// Begin TitleState.
TitleState::TitleState() {}

void TitleState::Enter()
{
	m_title = new Sprite({0,0,1160,350},{90,25,900,300},TEMA::GetTexture("title"));
	
	m_labels.push_back(new Label("Title",250,300, "Maxim Dobrivskiy",{200,200,255,255}));

	m_playButton = new PlayButton({(WIDTH - 400)/2,400,400,125});
	m_exitButton = new ExitButton({ (WIDTH - 400) / 2,600,400,125 });
}

void TitleState::Update()
{
	if (m_playButton->Update() == 1)
		return;
	if (m_exitButton->Update() == 1)
		return;
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 100, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	for (Label* label : m_labels)
	{
		label->Render();
	}

	m_playButton->Render();
	m_title->Render();
	m_exitButton->Render();
	
	State::Render();
}

void TitleState::Exit()
{
	for (Label* label : m_labels)
	{
		delete label;
	}
	
	delete m_title;
	delete m_exitButton;
	delete m_playButton;
}
// End TitleState.

// Begin GameState.

GameState::GameState()
{
	
}

void GameState::Enter()
{
	srand((unsigned)time(0));
	
	m_debugger = new DebugMode(this);

	m_player = new Player();

	SCMA::Init(m_player);

	m_gameHUD = new GameHUD(m_player);

	m_timer = new Label("Title", 750, 20, "Time: 0", { 200,200,255,255 });
	m_seconds = 0;
}

void GameState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_H))
	{
		m_debugger->SetMode(!m_debugger->GetMode());
	}
	
	m_player->update();
	
	m_gameHUD->Update();

	if (m_fullFrame++ > 60 and m_player->GetStatus() == ALIVE)
	{
		m_fullFrame = 0;
		m_seconds++;
	}

	std::string txt = "Time: " + std::to_string(m_seconds);
	m_timer->SetText(txt.c_str());
	
	UIMA::Update();

	SCMA::Update();

	CheckCollision();

	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PushState(new PauseState);
	}
	if (not m_player->IsAlive())
	{
		STMA::ChangeState(new EndState);
	}
}

void GameState::CheckCollision()
{
	COMA::CheckMapCollision(m_player);
	
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 64, 128, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	SCMA::Render();

	m_debugger->Draw();
	
	m_player->Render();

	m_gameHUD->Render();

	m_timer->Render();
	
	UIMA::Render(LOW);
	UIMA::Render(MEDIUM);
	UIMA::Render(HIGH);
	
}

void GameState::Exit()
{
	delete m_player;
	delete m_debugger;

	m_gameHUD->Clean();
	delete m_gameHUD;
	delete m_timer;

	SCMA::Clean();
}

void GameState::Resume() {}

// End GameState.

EndState::EndState()
{
}

void EndState::Enter()
{
	m_restartButton = new RestartButton({ (WIDTH - 400) / 2,250,400,125 });
	m_exitButton = new ExitButton({ (WIDTH - 400) / 2,420,400,125 });
	m_finish = false;
}

void EndState::Update()
{
	if (m_restartButton->Update() == 1)
		return;
	if (m_exitButton->Update() == 1)
		return;
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 180, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	
	m_restartButton->Render();
	m_exitButton->Render();
	
	State::Render();
}

void EndState::Exit()
{
	delete m_exitButton;
	delete m_restartButton;
}

// End ExitState.

// Begin PauseState.

PauseState::PauseState()
{}

void PauseState::Enter()
{
	m_blackScreen = new Sprite({ 0,0,64,64 }, { 0,0,WIDTH,HEIGHT }, TEMA::GetTexture("black_screen"));
	m_pauseLabel = new Sprite({ 0,0,500,200 }, { (WIDTH - 500) / 2,75,500,200 }, TEMA::GetTexture("pause"));
	m_resumeButton = new ResumeButton({ (WIDTH - 400) / 2,350,400,125 });
	m_exitButton = new ExitButton({ (WIDTH - 400) / 2,500,400,125 });
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		STMA::PopState();
		return;
	}
	if (m_resumeButton->Update() == 1)
		return;
	if (m_exitButton->Update() == 1)
		return;
}

void PauseState::Render()
{
	STMA::GetStates()[0]->Render();
	m_blackScreen->Render();
	m_pauseLabel->Render();
	m_resumeButton->Render();
	m_exitButton->Render();
}

void PauseState::Exit()
{
	delete m_blackScreen;
	delete m_resumeButton;
	delete m_exitButton;
	delete m_pauseLabel;
}

//End EndState
