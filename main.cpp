#include <vector>
#include <iostream>
#include "Board.h"

int main() {
	using namespace std;
	
	// Test the board class
	int dim{ 4 };

	vector<vector<int>> b(dim, vector<int>(dim, 0));
	for (int i = 0, tile = 1; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			b[i][j] = tile;
			++tile;
		}
	}

	b[3][3] = 0;

	Board board(b);

	cout << board << endl;
	cout << "The hamming cost: " << board.GetHamming() << endl;
	cout << "The manhattan cost: " << board.GetManhattan() << endl;

	cout << "Has the board reached the goal? ";
	if (board.IsGoal())
		cout << "Yes." << endl;
	else
		cout << "No." << endl;
}
