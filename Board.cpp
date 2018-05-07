#include "Board.h"

Board::Board(const std::vector<std::vector<int>>& blocks)
	: blocks_(blocks)
	, dimension_(blocks.size())
{}

int Board::GetDimension() const {
	return dimension_;
}

void Board::Hamming() const {
	int cost{ 0 };
	int count = 1;
	for (const auto& row : blocks_) {
		for (const auto& tile : row) {
			if (tile != count)
				++cost;
			++count;
		}
	}
	// Since 0 doesn't count as a tile, the cost caused by it must be subtracted
	hamming_cost_ = cost - 1;
}

void Board::Manhattan() const {
	int cost{ 0 };
	int count = 1;
	for (const auto& row : blocks_) {
		for (const auto& tile : row) {
			if (tile != count)
				++cost;
			++count;
		}
	}
	// Since 0 doesn't count as a tile, the cost caused by it must be subtracted
	hamming_cost_ = cost - 1;
}

int Board::GetHamming() const {
	if (hamming_cost_ < 0) {
		Hamming();
	}

	return hamming_cost_;
}


