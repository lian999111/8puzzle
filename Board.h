#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

class Board {
private:
	std::vector<std::vector<int>> blocks_;
	int dimension_{ 0 };

public:
	// Constructor
	//	 Input:
	//		blocks: a vector representing the board
	explicit Board(const std::vector<std::vector<int>>& blocks);

	// Destructor
	~Board() = default;

	// Gets the dimension of the board
	//	Output:
	//		the dimension of the board
	int GetDimension() const;

	// Computes the hamming cost
	//	Output:
	//		the hamming cost
	int Hamming() const;

	// Computes the manhattan cost
	//	Output:
	//		the manhattan cost
	//int Manhattan() const;

	// Checks if the board has reached the goad
	//	Output:
	//		true if is goal
	//bool IsGoal() const;

	// Returns a board that is obtained by exchanging any pair of blocks
	//	Output:
	//		a board that is obtained by exchanging any pair of blocks
	//Board Twin() const;

	// Checks if this board equals to the given board
	//	Input:
	//		board: a board to compare with
	//	Output:
	//		true if the boards are equal
	//bool Equals(const Board& board) const;

	// Returns a vector of neighbor boards
	//	Input:
	//		board: a board to compare with
	//	Output:
	//		true if the boards are equal
	//std::vector<Board> neighbors() const;

	// Operator << overloading
	friend std::ostream& operator<<(std::ostream& out, const Board& board) {
		out << board.dimension_ << '\n';
		for (auto&& row : board.blocks_) {
			for (auto&& tile : row) {
				out << std::setw(3) << std::right << tile;
			}
			out << '\n';
		}
			
		return out;
	}
};

