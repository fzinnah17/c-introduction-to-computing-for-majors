#include <iostream> 
#include <vector> 
#include <bits/stdc++.h>
#include <cstdlib>  
using namespace std; 

vector<int> deck; 
vector<int> pile;
vector<int> usedDeck;
int deckSize = 52;
char cardType[] = {'H', 'S', 'D', 'C'};
char cardNumberDeck[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'C', 'J', 'Q', 'K'};
vector<vector<int> > card(4); 

void deckbuild(){
	for(int i = 0; i <= 51; i++)
		deck.push_back(i);
	srand(time(0));
    random_shuffle(deck.begin(), deck.end()); 
	for (int i = 0; i < card.size(); i++) { 
        card[i] = vector<int>(6); 
        for (int j = 0; j < card[i].size(); j++) {
            card[i][j] = deck.back();
            deck.pop_back();        
		}
    }
    pile.push_back(deck.back());
    deck.pop_back(); 
}
bool checkWin(){
	for (int i = 0; i < card.size(); i++) { 
        if(card[i].size() == 0)
        	return true;
    }
    return false;
}
void deleteVector(int i, int turn){
	vector<int>::iterator position = find(card[turn].begin(), card[turn].end(), card[turn][i]);
	if (position != card[turn].end()) // == myVector.end() means the element was not found
    card[turn].erase(position);

}
char* currentCard(int no){
	char* c = (char*)malloc(2 * sizeof(char));
	if(no > 51 && no < 56){
		c[0] = '*';c[1] = '\0';
	}else if((no%13)==9){
		c[0]='1';c[1]='0';
	}
	else{
		c[0] = cardNumberDeck[no%13];c[1] = '\0';
	}
	return c;
}
void showCard(int no, char ch){
	 int i;
	 char c;
	 if(ch != '0')cout<<"\nPlayer "<<no;
	for (c = 'a',i=0;i<card[no].size();c++, i++){
		cout<<"  ("<<c<<") "<<cardType[(card[no][i] / 13)]<<currentCard(card[no][i]);
	}
	if(ch == '0'){
		cout<<"  ("<<c<<") draw";
	}
	cout<<endl;
}
bool checkChoice(char choice, int turn){
	if((int(choice)-97) > card[turn].size()){
		cout<<"First wrong"<<endl;
		return false;
	}
	else{
		if(currentCard(card[turn][(int(choice)-97)])[0] != '*' && currentCard(card[turn][(int(choice)-97)])[0] != '8' &&((((pile.back() > 51) && (pile.back() < 56))?(pile.back() -52):(pile.back() / 13)) != (card[turn][(int(choice)-97)] / 13)) && currentCard(pile.back()) != currentCard(card[turn][(int(choice)-97)])){
			return false;
		}
		return true;
	}
}
void addBack(){
	int t =pile.back();
	for(int i = 0; i < pile.size() - 1; i++){
		pile.pop_back();
		deck.push_back(pile.back());
	}
	pile.push_back(t);
	srand(time(0));
    random_shuffle(deck.begin(), deck.end());
}
void drawCard(int turn){
	int count = 0;
	while( cardType[(card[turn].back() / 13)] != (((pile.back() > 51) && (pile.back() < 56))?cardType[(pile.back() -52)]:cardType[(pile.back() / 13)]) && currentCard(deck.back())[0] !='8' ){
		cout<<"\n    Player "<<turn<<" drawing...";
		card[turn].push_back(deck.back());
		deck.pop_back();
		if(deck.size()==0){addBack();}
	}	
	cout<<"\n    Player "<<turn<<" choose "<<cardType[(card[turn].back() / 13)]<<currentCard(card[turn].back());
	pile.push_back(card[turn][card[turn].size()-1]);
	deleteVector(card[turn].size()-1, turn);
}
void addDummyInPile(char suit){
	if(suit=='H')
		pile.push_back(52);
	else if(suit=='S')
		pile.push_back(53);
	else if(suit=='D')
		pile.push_back(54);
	else if(suit=='C')
		pile.push_back(55);
}
int main() {
  	deckbuild();
  	int turn = 0;
  	while(!checkWin()){
  		char *c = (char*)malloc(2 * sizeof(char)), choice = 'z', suit = 'H';
		cout<<"\nPile has "<<(((pile.back() > 51) && (pile.back() < 56))?cardType[(pile.back() -52)]:cardType[(pile.back() / 13)])<<currentCard(pile.back());
		if(turn == 0){
			cout<<" <---- your turn"<<endl;
			cout<<"   ";
			showCard(0, '0');
			cout<<"\nWhich one to play? ";
			cin>>choice;
			while(choice != '?' && (int(choice)-97) != card[turn].size() && !checkChoice(choice, turn)){
				cout<<"\nWhich one to play? ";
				cin>>choice;
			}
			if(choice == '?'){
				for(int i=1; i<4; i++){
					showCard(i, choice);
				}
				turn -=1;
			}
			else if((int(choice)-97) == card[turn].size() ){
				card[turn].push_back(deck.back());
				deck.pop_back();
				turn -=1;
			}
			else if(currentCard(card[turn][(int(choice)-97)])[0] == '8' ){
				cout<<"	Which suit you want ? ";
				cin>>suit;
				deleteVector((int(choice)-97), turn);
				addDummyInPile(suit);
			}
			else{
				pile.push_back(card[turn][(int(choice)-97)]);
				deleteVector(int(choice)-97, 0);
			}
		}
		else{
			int i;
			for(i=0; i< card[turn].size();i++){
				if(checkChoice(char(i+97), turn)){
					break;
				}
			}
			if(i<card[turn].size()){
				pile.push_back(card[turn][i]);
				if(currentCard(card[turn][i])[0] == '8' ){
					cout<<"\n   Player "<<turn<<" choose "<<(((pile.back() > 51) && (pile.back() < 56))?cardType[(pile.back() -52)]:cardType[(pile.back() / 13)])<<currentCard(pile.back());
					cout<<"\n Player "<<turn<<" declared suite "<<cardType[(card[turn][0] / 13)];
					suit = cardType[(card[turn][0] / 13)];
					addDummyInPile(suit);
						
				}
				else
					cout<<"\n   Player "<<turn<<" choose "<<(((pile.back() > 51) && (pile.back() < 56))?cardType[(pile.back() -52)]:cardType[(pile.back() / 13)])<<currentCard(pile.back());
				deleteVector(i, turn);
			}
			else
				drawCard(turn);
		}
		turn = (turn + 1) % 4;
	}
	if(card[0].size() == 0)
		cout<<"\n\n\nYou won!";
	else
		cout<<"\n\n\n Player "<<((card[1].size() == 0)?"1":(card[2].size() == 0)?"2":"3")<<" Won\n";
	cout<<"\n[Final Card distribution]";
	showCard(0 ,'?');
	showCard(1, '?');
	showCard(2, '?');
	showCard(3, '?');
    return 0; 
} 