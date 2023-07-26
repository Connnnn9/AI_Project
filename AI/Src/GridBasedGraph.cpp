#include "Precomplied.h"
#include "GridBasedGraph.h"

using namespace AI;
void GridBasedGraph::Initialize(int colums, int rows)
{
	mNodes.clear();
	mNodes.reserve(colums * rows);
	mColumns = colums;
	mRows = rows;

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < colums; ++c)
		{
			auto& node = mNodes.emplace_back();
			node.column = c;
			node.row = r;
		}
	}
}

GridBasedGraph::Node* GridBasedGraph::GetNode(int x, int y)
{
	const int index = GetIndex(x, y);
	if (index < mNodes.size())
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