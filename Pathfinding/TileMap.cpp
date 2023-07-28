#include "TileMap.h"

using namespace AI;

namespace
{
	inline int ToIndex(int x, int y, int columns)
	{
		return x + (y * columns);
	}
}

void TileMap::LoadTiles(const char* fileName)
{
	if (!std::filesystem::exists(fileName))
		return;

	std::fstream file(fileName);

	int count = 0;
	std::string buffer;
	file >> buffer;
	file >> count;

	mTiles.clear();
	mTiles.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		int isblocked = 0;
		file >> buffer;
		file >> isblocked;

		Tile& tile = mTiles.emplace_back();
		tile.isBlocked = isblocked = 1;
		tile.textureid = X::LoadTexture(buffer.c_str());

	}
    file.close();

    mTileWidth = X::GetSpriteWidth(mTiles[0].textureid);
    mTileHeight = X::GetSpriteHeight(mTiles[0].textureid);
}

void TileMap::LoadMap(const char* fileName)
{
    if (!std::filesystem::exists(fileName))
    {
        return;
    }

    std::fstream file(fileName);

    int colums = 0;
    int rows = 0;
    std::string buffer;

    file >> buffer;
    file >> colums;
    file >> buffer;
    file >> rows;

    mColumns = colums;
    mRows = rows;

    mMap.resize(colums * rows);

    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < colums; ++x)
        {
            char tileType;
            file >> tileType;
            mMap[ToIndex(x, y, colums)] = tileType - '0';
        }
    }
    file.close();

    auto Getneighbor = [&](int c, int r) -> AI::GridBasedGraph::Node*
    {
        if (IsBlocked(c, r))
        {
            return nullptr;
        }

        return mGraph.GetNode(c, r);
    };

    mGraph.Initialize(mColumns, mRows);
    for (int  r = 0; r < mRows; ++r)
    {
        for (int  c = 0; c < mColumns; ++c)
        {
            if (IsBlocked(c,r))
            {
                continue;
            }
            GridBasedGraph::Node* node = mGraph.GetNode(c,r);
            node->neighbors[GridBasedGraph::Direction::North] = mGraph.GetNode(c, r - 1);
            node->neighbors[GridBasedGraph::Direction::South] = mGraph.GetNode(c, r + 1);
            node->neighbors[GridBasedGraph::Direction::East] = mGraph.GetNode(c + 1, r);
            node->neighbors[GridBasedGraph::Direction::West] = mGraph.GetNode(c - 1, r - 1);
            node->neighbors[GridBasedGraph::Direction::NorthEast] = mGraph.GetNode(c + 1, r - 1);
            node->neighbors[GridBasedGraph::Direction::NorthWest] = mGraph.GetNode(c - 1, r - 1);
            node->neighbors[GridBasedGraph::Direction::SouthEast] = mGraph.GetNode(c + 1, r + 1);
            node->neighbors[GridBasedGraph::Direction::SouthWest] = mGraph.GetNode(c - 1, r + 1);
        }
    }
}

void TileMap::Render() const
{
    float spriteWidth = X::GetSpriteWidth(mTiles[0].textureid);
    float spriteHeight = X::GetSpriteHeight(mTiles[0].textureid);
    X::Math::Vector2 position;
    for (int y = 0; y < mRows; ++y)
    {
        for (int x = 0; x < mColumns; ++x)
        {
            int index = ToIndex(x, y, mColumns);
            X::DrawSprite(mTiles[mMap[index]].textureid, position);
            position.x += spriteWidth;
        }

        position.x = 0.0f;
        position.y += spriteHeight;
    }
    for (int r = 0; r < mRows; ++r)
    {
        for (int c = 0; c < mColumns; ++c)
        {
            const auto node = mGraph.GetNode(c, r);
            for ( const auto neighbor : node->neighbors)
            {
                if (neighbor == nullptr)
                {
                    continue;
                }
                const auto a = GetPixelPosition(node->column, node->row);
                const auto b = GetPixelPosition(neighbor->column, neighbor->row);
                X::DrawScreenLine(a, b, X::Colors::Blue);
            }
        }
    }
}

bool TileMap::IsBlocked(int x, int y) const
{
    if (x >= 0 && x < mColumns && y >= 0 && y < mRows);
    {
        const int index = ToIndex(x, y, mColumns);
        if (index < mMap.size())
        {
            int tile = mMap[index];
            return mTiles[tile].isBlocked;
        }
    }
    return true;
}

Path TileMap::FindPathBFS(int Start_X, int Start_Y, int End_X, int End_Y)
{
    Path path;
    AI::Pathfinding::BFS bfs;
    if (bfs.Search(mGraph,Start_X,Start_Y,End_X,End_Y))
    {
        const auto& closedList = bfs.GetClosedList();
        auto node = closedList.back();
        while (node != nullptr)
        {
            path.push_back(GetPixelPosition(node->column, node->row));
            node = node->parent;
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

X::Math::Vector2 TileMap::GetPixelPosition(int x, int y) const
{
    return{
        (x + 0.5f) * mTileWidth,
        (y + 0.5f) * mTileHeight
    };
}

