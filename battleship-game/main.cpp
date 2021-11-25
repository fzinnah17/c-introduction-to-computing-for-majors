#include <iostream>
#include "Battleship.hpp"
using namespace std;

int main(){
	string command;   // user input command
	int row, col;     // row,col value of position command
	bool isHit;       // result of position command
	srand(time(0));
	Board board;
	cout << "There are 6 ships. Must bomb 18 places to destroy all..." << endl;
	cout << board << endl;
	bool done = false;
	while(!done){
		cout << endl << "Enter position,\"show\",\"init\" or \"quit\": ";
		getline(cin, command);
		COMMAND cmd = parseCommand(command, row, col);
		switch(cmd){
		case SHOW:
			board.setShow(true);cout << board << endl;board.setShow(false);break;
		case INIT:
			cout << "There are 6 ships. Must bomb 18 places to destroy all..." << endl;
			board.init();cout << board << endl;break;
		case POSITION:
			isHit = board.aimAt(row, col);
			if(!isHit && board.getCellAt(row, col) == '_') cout << "You missed :(" << endl;
			if(!isHit && board.getCellAt(row, col) == '@') cout << "You bombed same place...You missed :(" << endl;
			cout << board << endl;
			if(board.areAllShipsDestroyed()){
				cout << endl << "You destroyed all ship!!! Game WON..." << endl;done = true;
			}
			break;
		case QUIT:
			done = true;break;
		}
	}
	cout << "Bye..." << endl;
}
