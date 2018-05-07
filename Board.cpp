#include "Board.h"
#include <cstdlib>
#include <exception>

Board::Board(const std::vector<std::vector<int>>& blocks)
	: blocks_(blocks.size() > 1 ? blocks : throw std::invalid_argument("A board must have more than 1 block."))
	, dimension_(blocks.size())
{}

// This is a private ctor for Neighbors()'s internal use
Board::Board(const std::vector<std::vector<int>>& blocks, int manhattan_cost) 
	: blocks_(blocks.size() > 1 ? blocks : throw std::invalid_argument("A board must have more than 1 block."))
	, dimension_(blocks.size())
	, manhattan_cost_(manhattan_cost)
{}

bool Board::MoveBlock(std::vector<std::vector<int>>& copy_blocks, std::pair<int, int> blank_indices, std::pair<int, int> block_indices) const{
	// The block to be swapped with the blank
	int block_row = block_indices.first;
	int block_col = block_indices.second;
	const int& block = copy_blocks[block_row][block_col];

	// The indices of the blank
	int blank_row = blank_indices.first;
	int blank_col = blank_indices.second;

	// The indices of the goal of the block
	int goal_row = (block - 1) / blocks_.size();
	int goal_col = (block - 1) % blocks_.size();

	// Swap the block with the blank
	std::swap(copy_blocks[blank_row][blank_col], copy_blocks[block_row][block_col]);

	// Return if the block gets closer to its goal
	return abs(blank_col - goal_col) < abs(block_col - goal_col);
}

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
	int block{ 0 };
	int goal_row{ 0 }, goal_col{ 0 };

	for (std::vector<int>::size_type i = 0; i < blocks_.size(); ++ i) {
		for (std::vector<int>::size_type j = 0; j < blocks_[i].size(); ++j) {
			block = blocks_[i][j];

			// Since 0 doesn't count as a tile
			if (block == 0) {
				continue;
			}

			goal_row = (block - 1) / blocks_.size();
			goal_col = (block - 1) % blocks_.size();
			cost += abs(static_cast<int>(i - goal_row)) + abs(static_cast<int>(j - goal_col));
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

bool Board::operator==(const Board & rhs) const {

	if (this->dimension_ != rhs.dimension_)
		return false;

	for (std::vector<int>::size_type i = 0; i < blocks_.size(); ++i) {
		for (std::vector<int>::size_type j = 0; j < blocks_[i].size(); ++j) {
			if (this->blocks_[i][j] != rhs.blocks_[i][j]) {
				return false;
			}
		}
	}

	return true;
}

std::vector<Board> Board::Neighbors() const {
	std::vector<Board> neighbors;
	
	// Find the blank block
	int blank_row{ 0 }, blank_col{ 0 };

	for (std::vector<int>::size_type i = 0; i < blocks_.size(); ++i) {
		for (std::vector<int>::size_type j = 0; j < blocks_[i].size(); ++j) {
			if (blocks_[i][j] == 0) {
				blank_row = i;
				blank_col = j;
				// Breaking out of nested loops is one of few examples where "goto" is useful - by Stroustrup 
				goto loop_end;
			}
		}
	}
loop_end:

	// When the blank is not on the top edge
	if (blank_row > 0) {
		auto copy_blocks = this->blocks_;

		// The indices of the block to be swapped with the blank
		int block_row = blank_row - 1;
		int block_col = blank_col;

		bool is_closer = MoveBlock(copy_blocks, std::make_pair(blank_row, blank_col), std::make_pair(block_row, block_col));

		// If new place is nearer to the goal place, decrement the manhattan cost by 1
		if (is_closer) {
			// emplace_back cannot be used here since the ctor used here is private
			// thus the allocator cannot access the ctor to construct the Board object in-place
			// for further reference: https://stackoverflow.com/questions/17007977/vectoremplace-back-for-objects-with-a-private-constructor/17008204?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() - 1));
		}
		else {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() + 1));
		}
	}

	// When the blank is not on the bottom edge
	if (blank_row < (this->blocks_.size() - 1)) {
		auto copy_blocks = this->blocks_;

		// The indices of the block to be swapped with the blank
		int block_row = blank_row + 1;
		int block_col = blank_col;

		bool is_closer = MoveBlock(copy_blocks, std::make_pair(blank_row, blank_col), std::make_pair(block_row, block_col));

		// If new place is nearer to the goal place, decrement the manhattan cost by 1
		if (is_closer) {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() - 1));
		}
		else {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() + 1));
		}
	}

	// When the blank is not on the left edge
	if (blank_col > 0) {
		auto copy_blocks = this->blocks_;

		// The indices of the block to be swapped with the blank
		int block_row = blank_row;
		int block_col = blank_col - 1;

		bool is_closer = MoveBlock(copy_blocks, std::make_pair(blank_row, blank_col), std::make_pair(block_row, block_col));

		// If new place is nearer to the goal place, decrement the manhattan cost by 1
		if (is_closer) {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() - 1));
		}
		else {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() + 1));
		}
	}

	// When the blank is not on the right edge
	if (blank_col < (this->blocks_.size() - 1)) {
		auto copy_blocks = this->blocks_;

		// The indices of the block to be swapped with the blank
		int block_row = blank_row;
		int block_col = blank_col + 1;

		bool is_closer = MoveBlock(copy_blocks, std::make_pair(blank_row, blank_col), std::make_pair(block_row, block_col));

		// If new place is nearer to the goal place, decrement the manhattan cost by 1
		if (is_closer) {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() - 1));
		}
		else {
			neighbors.push_back(Board(copy_blocks, this->GetManhattan() + 1));
		}
	}
	
	return neighbors;
}


