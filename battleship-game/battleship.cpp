#include "Battleship.hpp"

void Board::init(){
	numOfHits = 0;grid.clear();show = false;
	for (int i = 0; i < BOARD_SIZE; i++) {
		vector<char> *row = new vector<char>();
		for (int j = 0; j < BOARD_SIZE; j++) row->push_back('.');
		grid.push_back(*row);
	}
	for(int i = 0; i < NUM_SHIPS; i++){
		bool placed = false;
		while (!placed) {
			int row = rand() % BOARD_SIZE, col = rand() % BOARD_SIZE, length = 2 + (rand() % 3);
			DIRECTION dir = (rand() % 2 == 0) ? DIRECTION::HORIZONTAL : DIRECTION::VERTICAL;
			placed = placeShip(row, col, length, dir);
		}
	}
}
bool Board::aimAt(int row, int col){
	if(row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return false;
	if(grid[row][col] == '*'){ grid[row][col] = '@'; return true;}
	if(grid[row][col] == '.'){ grid[row][col] = '_'; return false;}
	return false;
}
bool Board::areAllShipsDestroyed(){
	return numOfHits == TOTAL_HITS;
}
bool Board::placeShip(int &row, int &col, int length, DIRECTION &dir) {
	int r = row, c = col;
	for (int i = 0; i < length; i++) {
		if(r >= BOARD_SIZE || c >= BOARD_SIZE || grid[r][c] != '.') return false;
		if(dir == HORIZONTAL) c++; else r++;
	}
	for (int i = 0; i < length; i++) {
		grid[row][col] = '*';
		if(dir == HORIZONTAL) col++;else row++;
	}
	return true;
}

COMMAND parseCommand(string &command, int &row, int &col) {
	if (command == "show") return SHOW;
	if (command == "init") return INIT;
	if (command == "quit") return QUIT;
	stringstream ss(command);
	int posRow;
	char posCol;
	ss >> posRow >> posCol;
	posCol = toupper(posCol);
	row = posRow - 1; col = posCol - 'A';
	return POSITION;
}
