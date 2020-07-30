#include "PathManager.h"
#include "DebugManager.h"
#include "MathManager.h"
#include <iostream>

#include "CollisionManager.h"
#include "EnemyManager.h"

#define MAXCONNECTIONDISTANCE 200.0

std::vector<PathNode*> PAMA::s_nodes;

PathNode* PathManager::CreateNode(float x, float y)
{
	s_nodes.push_back(new PathNode(x * 32, y * 32));

	PathNode* back = s_nodes.back();
	SDL_FPoint backTemp = { back->x, back->y };
	
	for (PathNode* node : s_nodes)
	{
		SDL_FPoint temp = { node->x,node->y };
		float dist = MAMA::Distance(backTemp.x, temp.x, backTemp.y, temp.y);
		
		if (node != s_nodes.back() and COMA::LOSCheck(&backTemp,&temp)
			and dist < MAXCONNECTIONDISTANCE)
		{
			back->AddConnection(new PathConnection(back, node, dist));
			node->AddConnection(new PathConnection(node, back, dist));
		}
	}

	return back;
}

void PathManager::Clear()
{
	for (PathNode* node : s_nodes)
	{
		delete node;
	}
	s_nodes.clear();
	s_nodes.shrink_to_fit();
}

void PathManager::Update()
{
	for (PathNode* node : s_nodes)
	{
		SDL_FPoint temp = { node->x,node->y };
		node->SetPlayerLOS(COMA::LOSCheck(&ENMA::GetScene()->GetPlayer()->GetCenter(), &temp));
	}
}

void PathManager::GetShortestPath(PathNode* start, PathNode* goal)
{
	// std::cout << "Starting pathing..." << std::endl;
	s_path.clear(); // Clear the old saved path so we can save a new one.
	s_path.shrink_to_fit();
	NodeRecord* currentRecord = new NodeRecord(start);
	currentRecord->m_totalCost = start->Heuristic(); // Already we see an A* addition.
	s_open.push_back(currentRecord);
	while (s_open.size() > 0)
	{
		currentRecord = GetSmallestNode();
		// std::cout << "Doing node at: " << currentRecord->m_node->x << ',' << currentRecord->m_node->y << std::endl;
		// std::cout << "Found " << currentRecord->m_node->GetConnections().size() << " connections!" << std::endl;
		if (currentRecord->m_node == goal)
		{
			s_open.erase(std::remove(s_open.begin(), s_open.end(), currentRecord), s_open.end());
			s_closed.push_back(currentRecord);
			break; // We found the goal!
		}
		std::vector<PathConnection*> connections = currentRecord->m_node->GetConnections();
		for (unsigned i = 0; i < connections.size(); i++)
		{
			// std::cout << "Doing connection " << i << std::endl;
			PathNode* endNode = connections[i]->GetToNode();
			NodeRecord* endNodeRecord;
			double endNodeCost = currentRecord->m_costSoFar + connections[i]->GetCost();

			if (ContainsNode(s_closed, endNode))
			{
				endNodeRecord = GetNodeRecord(s_closed, endNode);
				if (endNodeRecord->m_costSoFar <= endNodeCost)
					continue;
				s_closed.erase(std::remove(s_closed.begin(), s_closed.end(), endNodeRecord), s_closed.end());
				// Node gets pushed into open list below... lines 56/57.
			}
			else if (ContainsNode(s_open, endNode))
			{
				endNodeRecord = GetNodeRecord(s_open, endNode);
				if (endNodeRecord->m_costSoFar <= endNodeCost)
					continue;
			}
			else
			{
				endNodeRecord = new NodeRecord();
				endNodeRecord->m_node = endNode;
			}
			endNodeRecord->m_costSoFar = endNodeCost;
			endNodeRecord->m_connection = connections[i];
			endNodeRecord->m_fromRecord = currentRecord;
			endNodeRecord->m_totalCost = endNodeCost + endNode->Heuristic();
			if (!ContainsNode(s_open, endNode))
				s_open.push_back(endNodeRecord);
		}
		s_open.erase(std::remove(s_open.begin(), s_open.end(), currentRecord), s_open.end());
		s_closed.push_back(currentRecord);
		// std::cout << "Open size: " << s_open.size() << std::endl;
	}
	// std::cout << "Done while loop, open size:" << s_open.size() << std::endl;
	if (currentRecord->m_node != goal)
	{
		std::cout << "Could not find path!" << std::endl;
	}
	else
	{
		// std::cout << "Found goal at: [" << currentRecord->m_node->y / 32 << ',' << currentRecord->m_node->x / 32 << ']' << std::endl;
		while (currentRecord->m_node != start)
		{
			//std::cout << "Doing record for: [" << currentRecord->m_node->y/32 << ',' << currentRecord->m_node->x/32 << ']' << std::endl;
			s_path.push_back(currentRecord->m_connection);
			currentRecord = currentRecord->m_fromRecord;
		}
		std::reverse(s_path.begin(), s_path.end());
	}
	// Clean up lists. Uncomment the cout below to see how many records we have to clean up.
	// std::cout << "Cleaning up..." << "open size: " << s_open.size() << " | closed size: " << s_closed.size() << std::endl;
	for (unsigned i = 0; i < s_open.size(); i++)
	{
		delete s_open[i];
		s_open[i] = nullptr; // Wrangle your dangle.
	}
	s_open.clear();
	s_open.shrink_to_fit();
	for (unsigned i = 0; i < s_closed.size(); i++)
	{
		delete s_closed[i];
		s_closed[i] = nullptr; // Wrangle your dangle.
	}
	s_closed.clear();
	s_closed.shrink_to_fit();
}

NodeRecord* PathManager::GetSmallestNode()
{
	std::vector<NodeRecord*>::iterator smallest = s_open.begin();
	std::vector<NodeRecord*>::iterator current = s_open.begin();

	while (++current != s_open.end())
	{
		if ((*current)->m_totalCost < (*smallest)->m_totalCost)
			smallest = current;
		else if ((*current)->m_totalCost == (*smallest)->m_totalCost) // If equal, flip a coin!
			smallest = (rand() % 2 ? current : smallest);
	}
	return (*smallest);
}

std::vector<NodeRecord*>& PathManager::OpenList()
{
	return s_open;
}

std::vector<NodeRecord*>& PathManager::ClosedList()
{
	return s_closed;
}

bool PathManager::ContainsNode(std::vector<NodeRecord*>& list, PathNode* n)
{
	for (unsigned i = 0; i < list.size(); i++)
		if (list[i]->m_node == n)
			return true;
	return false;
}

NodeRecord* PathManager::GetNodeRecord(std::vector<NodeRecord*>& list, PathNode* n)
{
	for (unsigned i = 0; i < list.size(); i++)
		if (list[i]->m_node == n)
			return list[i];
	return nullptr;
}

double PathManager::HEuclid(const PathNode* start, const PathNode* goal)
{
	return MAMA::Distance(start->x, goal->x, start->y, goal->y);
}

double PathManager::HManhat(const PathNode* start, const PathNode* goal)
{
	return (std::abs(start->x - goal->x) + std::abs(start->y - goal->y));
}

void PathManager::DrawPath()
{
	for (unsigned i = 0; i < s_path.size(); i++)
	{
		/*DEMA::QueueLine({ s_path[i]->GetFromNode()->x + 16, s_path[i]->GetFromNode()->y + 16 },
			{ MAMA::HalfwayPoint(s_path[i]->GetFromNode()->Point(), s_path[i]->GetToNode()->Point()).x + 16,
			MAMA::HalfwayPoint(s_path[i]->GetFromNode()->Point(), s_path[i]->GetToNode()->Point()).y + 16 }, { 255,0,0,255 });
		DEMA::QueueLine({ MAMA::HalfwayPoint(s_path[i]->GetFromNode()->Point(), s_path[i]->GetToNode()->Point()).x + 16,
			MAMA::HalfwayPoint(s_path[i]->GetFromNode()->Point(), s_path[i]->GetToNode()->Point()).y + 16 },
			{ s_path[i]->GetToNode()->x + 16, s_path[i]->GetToNode()->y + 16 }, { 0,255,0,255 });*/
	}
}

double PathManager::getTotalPathCost()
{
	double totalCost = 0.0;
	for (PathConnection* connection : s_path)
	{
		totalCost += connection->GetCost();
	}
	return totalCost;
}

void PathManager::ClearPath()
{
	s_path.clear();
	s_path.shrink_to_fit();
}

std::vector<NodeRecord*> PathManager::s_open;
std::vector<NodeRecord*> PathManager::s_closed;

// Returned path to go here?
std::vector<PathConnection*> PathManager::s_path;