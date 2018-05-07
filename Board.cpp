#include "Board.h"
#include <cstdlib>
#include <exception>

Board::Board(const std::vector<std::vector<int>>& blocks)
	: blocks_(blocks.size() > 1 ? blocks : throw std::invalid_argument("A board must have more than 1 block."))
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
	int tile{ 0 };
	int goal_idx_i{ 0 }, goal_idx_j{ 0 };

	for (std::vector<int>::size_type i = 0; i < blocks_.size(); ++ i) {
		for (std::vector<int>::size_type j = 0; j < blocks_[i].size(); ++j) {
			tile = blocks_[i][j];

			// Since 0 doesn't count as a tile
			if (tile == 0) {
				continue;
			}

			goal_idx_i = (tile - 1) / blocks_.size();
			goal_idx_j = (tile - 1) % blocks_.size();
			cost += abs(static_cast<int>(i - goal_idx_i)) + abs(static_cast<int>(j - goal_idx_j));
		}
	}
	
	manhattan_cost_ = cost;
}

int Board::GetHamming() const {
	if (hamming_cost_ < 0) {
		Hamming();
	}

	return hamming_cost_;
}

int Board::GetManhattan() const {
	if (manhattan_cost_ < 0) {
		Manhattan();
	}

	return manhattan_cost_;
}

bool Board::IsGoal() const {
	int goal_tile = 1;

	for (const auto& row : blocks_) {
		for (const auto& tile : row) {
			if (tile != goal_tile)
				return false;
			
			++goal_tile;
			// The last block is zero and should not be used to check if the goal is reached
			if (goal_tile == blocks_.size() * blocks_.size())
				break;
		}
	}

	return true;
}

Board Board::Twin() const {
	auto blocks_copy = this->blocks_;
	
	int last_value = blocks_copy[0][0];
	int curr_value{ 0 };

	// The way of swapping is hard-coded, but it shall cover all the possible cases
	// Done by checking whether one of the first two blocks is 0 and taking the corresponding measure
	if (blocks_copy[0][0] == 0) {
		std::swap(blocks_copy[1][0], blocks_copy[0][1]);
	}
	else if (blocks_copy[0][1] == 0) {
		std::swap(blocks_copy[0][0], blocks_copy[1][0]);
	}
	else {
		std::swap(blocks_copy[0][0], blocks_copy[0][1]);
	}

	return Board(blocks_copy);
}


