#include "Solver.h"
#include <queue>
#include <memory>

struct Solver::SearchNode {	
	Board board{ {{1, 2}, {3, 0}} };	// A board with dim < 2 is illegal
	int num_of_moves{ 0 };
	int total_cost_manhattan{ 0 };
	std::shared_ptr<SearchNode> p_parent_node{ nullptr };

	// Note:
	//	Gernerally, a search node's parent will potentially get changed through the A* search
	//	process. And the A* algorithm needs to keep runing until all open nodes are explored
	//	to make sure the shortest path is found. Thus, typically the parents are recorded using
	//	a map data structure which allows convenient parent modifying.
	//
	//	In this assignment, the heuristic is said to be both admissible and consistent. That is,
	//	the first seach node that corresponds to the goal is exactly the shortest way to get it.
	//	For this reason, here only an observing raw pointer is needed to track the sequence.
	
	SearchNode() = default;

	SearchNode(const Board& board, const int& num_of_moves, const std::shared_ptr<SearchNode>& p_parent_node)
		: board(board)
		, num_of_moves(num_of_moves)
		, total_cost_manhattan(board.GetManhattan() + num_of_moves)
		, p_parent_node(p_parent_node)
	{}
};

struct Solver::NodesComparator {
	bool operator()(const SearchNode& lhs, const SearchNode& rhs) {
		if (lhs.total_cost_manhattan > rhs.total_cost_manhattan) {
			return true;
		}
		// Use hamming cost to break ties
		else if (lhs.total_cost_manhattan == rhs.total_cost_manhattan) {
			return lhs.board.GetHamming() > rhs.board.GetHamming();
		}
		else {
			return false;
		}
	}
};




Solver::Solver(const Board& board)
	: init_board_(board)
{

	Board init_twin_board(init_board_.Twin());

	// The priority queue: <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type >>
	// The pq is a local variable that will get eliminated when the solution has been finished in the ctor

	// This implementation takes the optimization that uses only one prioirty queue
	std::priority_queue<SearchNode, std::vector<SearchNode>, NodesComparator> min_pq;
	min_pq.emplace(init_board_, 0, nullptr);
	min_pq.emplace(init_twin_board, 0, nullptr);

	SearchNode curr_node;
	//std::vector<SearchNode> explored_nodes;

	while (true) {
		if (min_pq.size() == 0) {
			break;
		}
		curr_node = min_pq.top();
		min_pq.pop();

		if (curr_node.board.IsGoal()) {
			break;	// Goal found
		}

		auto p_curr_node = std::make_shared<SearchNode>(curr_node);
		std::vector<Board> neighbor_boards = curr_node.board.Neighbors();

		for (const auto& new_board : neighbor_boards) {
			if (curr_node.p_parent_node != nullptr && new_board == curr_node.p_parent_node->board) {
				continue;
			}
			min_pq.emplace(new_board, curr_node.num_of_moves + 1, p_curr_node);
		}
	}

	solution_.push_back(curr_node.board);
	num_of_moves_ = curr_node.num_of_moves;

	while (curr_node.p_parent_node != nullptr) {
		solution_.push_back(curr_node.board);
		curr_node = *(curr_node.p_parent_node);
	}

	if (curr_node.board == init_twin_board) {
		is_solvable_ = false;
		// Clear the solustion since its for the twin board
		solution_.clear();
		num_of_moves_ = -1;
	}

}

std::vector<Board> Solver::GetSolution() const {
	return solution_;
}

bool Solver::IsSolvable() const {
	return is_solvable_;
}

