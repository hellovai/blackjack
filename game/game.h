//=================================
// include guard
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Game {
	bool debug;

	bool my_status;
	vector<stateaction> moveList;
	int player_sum;
	int dealer_sum;
	int player_count;
	int dealer_count;
	Card revealed;
	vector<Card> deck;
	bool usable_ace;
	bool dealer_usable_ace;
	void CheckBust();
	void Deal(bool);
	void Deal() { Deal(true); };
public:
	Game();
	void setDebug( bool x ) {debug = x;};
	void Reset();
	bool Status() { return my_status; };	//checks if finished
	Card Revealed() { return revealed; };
	int Sum() { return player_sum; };
	bool Ace() { return usable_ace; };

	void Dealer();
	void Eval();
	void Move(Action );							// makes a move if valid
	vector<stateaction> History() { return moveList; };
	int Result();

};

//=================================
// end guard
#endif
//=================================
