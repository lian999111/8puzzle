#pragma once

#include <vector>
#include "Board.h"

class Solver {
private:
	const Board init_board_;
	mutable int num_of_moves_{ -1 };
	mutable std::vector<Board> solution_;
	mutable bool is_solvable_{ true };

	struct SearchNode;
	struct NodesComparator;

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
	//int GetMoves();

	// Getter of the solution sequence
	//	Output:
	//		A vector consisting of a sequence of boards following which the board can be solved
	std::vector<Board> GetSolution() const;

	// Returns whether the initial board is solvable
	//	Output:
	//		A boolean indicating the initial board can be solved
	bool IsSolvable() const;
};

