#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <utility>

class Board {
private:
	std::vector<std::vector<int>> blocks_;
	int dimension_{ 0 };
	mutable int hamming_cost_{ -1 };
	mutable int manhattan_cost_{ -1 };

	// Computes the hamming cost and save it in the instance variable
	void Hamming() const;

	// Computes the manhattan cost
	void Manhattan() const;

	// This ctor is for Neighbor()'s use. It allows directly assigning the manhattan cost
	// which can be computed fast inside Neighbor() by considering only the block be moved
	//	Input:
	//		blocks: a vector representing the board
	//		prev_manhattan: the manhattan cost of its parent board
	Board(const std::vector<std::vector<int>>& blocks, const int& parent_manhatten_cost);

	// Moves a block adjacent to the blank to the position of blank and returns the goal indices of the block
	// This method does NOT modify the object of itself. Instead, it's an utility method used in Neighbor() to 
	// move the block of a copied 2-D vector that is used to construct a new Board.
	//	Input:
	//		blocks: a 2-D vector representing the content of a board
	//		blank_indices: a pair of int representing the indices of the blank
	//		block_indices: a pair of int representing the indices of the block
	// Output:
	//		blocks: 2 blocks of the 2-D vector are swapped internally
	//		An boolean indicating whether the moved block gets closer to its goal
	bool MoveBlock(std::vector<std::vector<int>>& blocks, const std::pair<int, int>& blank_indices, const std::pair<int, int>& block_indices) const;

public:
	// Constructor
	//	 Input:
	//		blocks: a vector representing the board
	explicit Board(const std::vector<std::vector<int>>& blocks);

	// Copy ctor, Move ctor, Copy assignment, Move assignment, Destructor are declared implicitly

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
	bool IsGoal() const;

	// Returns a board that is obtained by exchanging any pair of blocks
	//	Output:
	//		a board that is obtained by exchanging any pair of blocks
	Board Twin() const;

	// Checks if this board equals to the given board
	//	Input:
	//		board: a board to compare with
	//	Output:
	//		true if the boards are equal
	bool operator==(const Board& rhs) const;

	// Returns a vector of neighbor boards
	//	Input:
	//		board: a board to compare with
	//	Output:
	//		true if the boards are equal
	std::vector<Board> Neighbors() const;

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

