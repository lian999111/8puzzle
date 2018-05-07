#include <vector>
#include <iostream>
#include "Board.h"

int main() {
	using namespace std;
	
	// Test the board class
	int dim{ 4 };

	vector<vector<int>> b(dim, vector<int>(dim, 0));
	for (int i = 0, tile = 0; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {
			b[i][j] = tile;
			++tile;
		}
	}

	Board board(b);

	cout << board << endl;
	cout << "The hamming cost: " << board.GetHamming() << endl;
	cout << "The manhattan cost: " << board.GetManhattan() << endl;

}
