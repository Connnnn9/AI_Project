#include "Precomplied.h"
#include "BFS.h"

using namespace AI::Pathfinding;

bool BFS::Search(GridBasedGraph & graph, int startX, int startY, int endX, int endY /*,std::function<bool(int, int)> isBlocked*/)
{
	graph.ResetSearchParams();
	auto node = graph.GetNode(startX, startY);
	mOpenList.push_back(node);
	node->opened = true;

	bool found = false;
	while (!found && !mOpenList.empty())
	{
		if (node == graph.GetNode(endX, endY))
		{
			found = true;
		}

		for (const auto &neighbor : node->neighbors)
		{
			if (neighbor != nullptr)
			{

				//if (isBlocked(neighbor->column, neighbor->row))
				//	continue;
				if (neighbor->opened)
					continue;
				if (!neighbor->closed)
				{
					neighbor->opened = true;
					mOpenList.push_back(neighbor);
					neighbor->parent = node;
				}
			}
		}
		node->closed = true;
		mClosedList.push_back(node);
		mOpenList.remove(node);
		if (!mOpenList.empty())
		{
			node = mOpenList.front();
			node->opened = true;
		}
	}
	return found;
}
