#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"
#include "Solver.h"

int main() {
	using namespace std;
	
	// Test the board class
	int dim{ 4 };

	vector<vector<int>> b = { { 5, 3, 1, 4 },{ 10, 2, 8, 7 },{ 14, 13, 0, 11 }, { 6, 9, 15, 12 } };

	Board board(b);

	cout << board << endl;
	cout << "The hamming cost: " << board.GetHamming() << endl;
	cout << "The manhattan cost: " << board.GetManhattan() << endl;

	cout << "Has the board reached the goal? ";
	if (board.IsGoal())
		cout << "Yes." << endl;
	else
		cout << "No." << endl;

	// Test Twin()
	cout << endl;
	cout << "The twin:" << endl;
	cout << board.Twin();

	// Test operator==
	cout << endl;
	cout << "The board and the twin are the same? ";
	if (board == board.Twin())
		cout << "Yes." << endl;
	else
		cout << "No." << endl;

	// Test a board with only 1 tile
	cout << endl;
	cout << "Test a board with only 1 tile: " << endl;
	vector<vector<int>> b_wrong{ {{0}} };

	try {
		Board board_1(b_wrong);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	// Test Neighbor()
	vector<vector<int>> b_1 = { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 10, 0, 11, 12 },{ 9, 13, 14, 15 } };
	Board board_1(b_1);
	auto neighbors = board_1.Neighbors();
	cout << "board_2: \n" << board_1;
	cout << "\nNeighbors of board_2: \n";
	for (const auto neighbor : neighbors) {
		cout << neighbor;
	}

	// Test Solver
	string filename{ "data/puzzle36.txt" };
	cout << "\nTest Solver on " << filename << endl;

	ifstream file;
	file.open(filename);

	file >> dim;
	vector<vector<int>> puzzle_from_file(dim, vector<int>(dim));

	int block{ 0 };
	for (int i = 0; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			file >> block;
			puzzle_from_file[i][j] = block;
		}
	}

	file.close();

	Board test_board(puzzle_from_file);
	cout << test_board;

	Solver board_solver(test_board);

	cout << "The board is ";
	if (board_solver.IsSolvable())
		cout << "solvable with " << board_solver.GetMoves() << " steps \n";
	else
		cout << "unsolvable \n";

	cout << "\n Solution sequence: \n";

	auto& solution = board_solver.GetSolution();
	for (auto ite = solution.rbegin(); ite != solution.rend(); ++ite) {
		cout << *ite;
	}
}
