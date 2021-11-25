#ifndef BATTLESHIP_HPP_
#define BATTLESHIP_HPP_
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <cctype>
#define TOTAL_HITS 18   // total hits required to destroy all ships
#define BOARD_SIZE 10   // size of the battleship board
#define NUM_SHIPS 6     // number of ships in the battelship game
using namespace std;
enum COMMAND { SHOW, INIT, QUIT, POSITION };
enum DIRECTION { HORIZONTAL, VERTICAL };

class Board{ // The class to define and implement the battleship board
public:
	Board(){init();};
	~Board(){};
	void init();
	void setShow(bool flag){show = flag;};
	bool aimAt(int row, int col);
	bool areAllShipsDestroyed();
	char getCellAt(int row, int col){ return grid[row][col];}
	friend ostream &operator<<(ostream &out, const Board &b){
		out << "  <<Pacific Ocean>>" << endl << "  ";
		for(int i = 0; i < BOARD_SIZE; i++) { out << " " << (char)('A' + i);}
		out << endl;
		for(int i = 0; i < BOARD_SIZE; i++){
			if(i < 9) { out << " "; out << (i+1) << " "; }
			for(int j = 0; j < BOARD_SIZE; j++){
				char c = b.grid[i][j];
				if(b.show && b.grid[i][j] == '*') out << "* ";
				else if(!b.show && b.grid[i][j] == '*') {out << ". ";}
				else out << c << " ";
			}
			out << endl;
		}
		return out;
	}
private:
	bool placeShip(int& row, int& col, int length, DIRECTION& dir);
	vector<vector<char> > grid;
	int numOfHits;
	bool show;
};
COMMAND parseCommand(string& command, int& row, int& col);
#endif /* BATTLESHIP_HPP_ */
