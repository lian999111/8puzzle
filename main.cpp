#include <vector>
#include <iostream>
#include "Board.h"

int main() {
	using namespace std;
	
	// Test the board class
	int dim{ 4 };

	vector<vector<int>> b(dim, vector<int>(dim, 0));
	for (int i = 0, block = 0; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			b[i][j] = block;
			++block;
		}
	}

	//b[3][3] = 0;

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
	dim = 1;
	vector<vector<int>> b_wrong(dim, vector<int>(dim, 0));
	for (int i = 0, tile = 1; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			b[i][j] = tile;
			++tile;
		}
	}

	try {
		Board board_1(b_wrong);
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}

	// Test Neighbor()
	vector<vector<int>> b_1 = { {3, 0, 1}, {2, 4, 5}, {6, 7, 8} };
	Board board_1(b_1);
	auto neighbors = board_1.Neighbors();
	cout << "board_2: \n" << board_1;
	cout << "\nNeighbors of board_2: \n";
	for (const auto neighbor : neighbors) {
		cout << neighbor;
	}
}
