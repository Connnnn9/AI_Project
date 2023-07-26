#pragma once

namespace AI
{
	class GridBasedGraph
	{

	public:
		enum class Direction
		{
			North,
			South,
			East,
			West,
			NorthWest,
			SouthWest,
			NorthEast,
			SouthEest
		};
		struct Node
		{
			std::array<Node*, 8> neighbors = {};
			int column = 0;
			int row = 0;
		};
		void Initialize(int colums, int rows);

		Node* GetNode(int x, int y);
		const Node* GetNode(int x, int y) const;

		int GetColums() const { return mColumns; }
		int GetColums() const { return mRows; }

	private:
		int GetIndex(int x, int y) const;

		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;

	};
}
