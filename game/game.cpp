#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>

#include "main.h"
#include "game.h"

using namespace std;

Game::Game() {
	debug = false;
	Reset();
}

void Game::Reset() {
	if(debug) cout<<"Starting round"<<endl;
	my_status = true;
	moveList.clear();
	usable_ace = false;
	dealer_usable_ace = false;
	player_count = 0;
	dealer_count = 0;
	player_sum = 0;
	dealer_sum = 0;
	Card arr[52] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, FACE, FACE, FACE, FACE, 
			ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, FACE, FACE, FACE, FACE, 
			ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, FACE, FACE, FACE, FACE, 
			ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, FACE, FACE, FACE, FACE };
	
	deck.clear();
	for(int i = 0; i < 52; i++)
		deck.push_back(arr[i]);

	random_shuffle(deck.begin(), deck.end());
	Deal();
	Deal(false);
	Deal();
	Deal(false);
	while(player_sum < 12)
		Deal();
}

void Game::Move(Action taken) {
	moveList.push_back(stateaction(player_sum, usable_ace, taken));
	switch(taken) {
		case STAY:
			my_status = false;
			break;
		case HIT:
			Deal();
			break;
	}
	CheckBust();
}

//private functions
void Game::Deal(bool player = true) {
	Card top = deck[0];
	deck.erase(deck.begin());
	if(player) {
		player_sum += top;
		if(usable_ace) {
			if(player_sum > 21) {
				usable_ace = false;
				player_sum -= 10;
			}
		} else if(top == ACE && player_sum < 12 ){
			usable_ace = true;
			player_sum += 10;
		}
		player_count++;
	} else {
		if(dealer_count == 0) revealed = top;
		dealer_sum += top;
		if(dealer_usable_ace) {
			if(dealer_sum > 21) {
				dealer_usable_ace = false;
				dealer_sum -= 10;
			}
		} else if(top == ACE && dealer_sum < 12 ){
			dealer_usable_ace = true;
			dealer_sum += 10;
		}
		dealer_count++;
	}
	if(debug) cout<<"Dealt: "<<top<<" to "<<(player ? "Player" : "Dealer")<<endl;
}

void Game::Dealer() {
	while(dealer_sum < 17) {
		if(debug) cout<<"Dealer Hit"<<endl;
		Deal(false);
	}
}

void Game::Eval() {
	cout<<"Dealer has: "<<revealed<<endl;
	cout<<"Player sum: "<<player_sum<<endl;
	if(debug) cout<<"\tUsable Ace: "<<(usable_ace ? "Yes" : "No")<<endl;
	if(debug) cout<<"Dealer sum: "<<dealer_sum<<endl;
	if(debug) cout<<"\tUsable Ace: "<<(dealer_usable_ace ? "Yes" : "No")<<endl;
}

int Game::Result() {
	if(player_sum > 21) return -1;
	else if (dealer_sum > 21) return 1;
	else if (player_sum > dealer_sum) return 1;
	else if (player_sum < dealer_sum) return -1;
	else return 0;
}

void Game::CheckBust() {
	if(player_sum > 21 ) {
		if(debug) cout<<"Bust!"<<endl;
		my_status = false;
		moveList.push_back(stateaction(player_sum, usable_ace, BUST));
	}
}