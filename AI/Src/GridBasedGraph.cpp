#include "Precomplied.h"
#include "GridBasedGraph.h"

using namespace AI;
void GridBasedGraph::Initialize(int columns, int rows)
{
	mNodes.clear();
	mNodes.resize(columns * rows);
	mColumns = columns;
	mRows = rows;

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			auto node = GetNode(c, r);
			for (int d = 0; d < 8; d++)
			{
				switch (d)
				{
				case 0:
					node->neighbors[d] = GetNode(c, r - 1);
					break;
				case 1:
					node->neighbors[d] = GetNode(c, r + 1);
					break;
				case 2:
					node->neighbors[d] = GetNode(c + 1, r);
					break;
				case 3:
					node->neighbors[d] = GetNode(c - 1, r);
					break;
				case 4:
					node->neighbors[d] = GetNode(c + 1, r - 1);
					break;
				case 5:
					node->neighbors[d] = GetNode(c - 1, r - 1);
					break;
				case 6:
					node->neighbors[d] = GetNode(c + 1, r + 1);
					break;
				case 7:
					node->neighbors[d] = GetNode(c - 1, r + 1);
					break;
				default:
					break;
				}
			}
			node->column = c;
			node->row = r;
		}
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	const int index = GetIndex(x, y);
	if (index< mNodes.size())
	{
		return &mNodes[index];
	}
	return nullptr;
}

const GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y) const
{
	const int index = GetIndex(x, y);
	if (index < mNodes.size())
	{
		return &mNodes[index];
	}
	return nullptr;
}

int GridBasedGraph::GetIndex(int x, int y) const
{
	return x + (y * mColumns);
}

void GridBasedGraph::ResetSearchParams()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.g = 0.0f;
		node.h = 0.0f;
		node.opened = false;
		node.closed = false;
	}
}