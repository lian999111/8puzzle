#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

class Board {
private:
	std::vector<std::vector<int>> blocks_;
	const int dimension_{ 0 };
	mutable int hamming_cost_{ -1 };
	mutable int manhattan_cost_{ -1 };

	// Computes the hamming cost and save it in the instance variable
	void Hamming() const;

	// Computes the manhattan cost
	void Manhattan() const;

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

	// Gets the hamming cost of the board
	//	Output:
	//		the hamming cost of the board
	int GetHamming() const;

	// Gets the manhattan cost of the board
	//	Output:
	//		the manhattn cost of the board
	int GetManhattan() const;

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
		out << "Dim: " << board.dimension_ << '\n';
		for (const auto& row : board.blocks_) {
			for (const auto& tile : row) {
				out << std::setw(3) << std::right << tile;
			}
			out << '\n';
		}
			
		return out;
	}
};

