#include "Board.h"

Board::Board(const std::vector<std::vector<int>>& blocks)
	: blocks_(blocks)
	, dimension_(blocks.size())
{}

int Board::GetDimension() const {
	return dimension_;
}

int Board::Hamming() const {
	int cost{ 0 };
	int count = 1;
	for (auto&& row : blocks_) {
		for (auto&& tile : row) {
			if (tile != count)
				++cost;
			++count;
		}
	}
	// Since 0 doesn't count as a tile, the cost caused by it must be subtracted
	return cost - 1;
}


