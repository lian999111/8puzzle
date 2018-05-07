#pragma once

#include <vector>
#include "Board.h"

class Solver {
private:
	int moves_{ -1 };
	std::vector<Board> solution_;

	class SearchNode;

public:
	// Constructor
	//	Input:
	//		board: the initial board to be solved
	Solver(const Board& board);

	// Destructor
	~Solver() = default;

	// Getter of the number of moves to solve the board
	//	Output:
	//		The number of moves
	int GetMoves();

	// Getter of the solution sequence
	//	Output:
	//		A vector consisting of a sequence of boards following which the board can be solved
	std::vector<Board> GetSolution();

	// Returns whether the initial board is solvable
	//	Output:
	//		A boolean indicating the initial board can be solved
	bool IsSolvable();
};

