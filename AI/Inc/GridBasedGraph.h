#pragma once

namespace AI
{
	class GridBasedGraph
	{
	public:
		enum Direction
		{
			North,
			South,
			East,
			West,
			NorthWest,
			SouthWest,
			NorthEast,
			SouthEast
		};
		struct Node
		{
			std::array<Node*, 8> neighbors = {};
			int column = 0;
			int row = 0;

			Node* parent = nullptr;
			float g = 0.0f;
			float h = 0.0f;
			bool opened = false;
			bool closed = false;
		};
		void Initialize(int colums, int rows);
		void ResetSearchParams();

		Node* GetNode(int x, int y);

		const Node* GetNode(int x, int y) const;

		int GetColumns() const { return mColumns; }
		int GetmRows() const { return mRows; }

	private:
		int GetIndex(int x, int y) const;

		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;
	};
}
