#include "TileMap.h"

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

		Tile tile = mTiles.emplace_back();
		tile.canWalk = isblocked = 1;
		tile.textureid = X::LoadTexture(buffer.c_str());

	}
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
}

// 2D map - 5 columns x 4 rows
// [0][0][0][0][0]
// [0][0][0][0][0]
// [0][0][0][X][0]   X is at (3, 2)
// [0][0][0][0][0]

// Stored as 1D - 5x4 = 20 slots
// [0][0][0][0][0] [0][0][0][0][0] [0][0][0][X][0] [0][0][0][0][0]
//
// index = column + (row * columnCount)
//       = 3 + (2 * 5)
//       = 13