#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;

int main(int argc, char* argv[]) {	
	srand ( time(NULL) );

	int gameCounter = 1;
	bool debug = false;
	string dumpfile = "data";
	//read arguments and define variable based on them
	for(int i=1; i<argc; i++) {
		string temp = argv[i];
		if (temp.compare("-debug") == 0) {
			debug = true;
		} else if (temp.compare("-g") == 0) {
			if(++i<argc)
				gameCounter = atoi(argv[i]);
			else
				usage_err(temp);
		} else if (temp.compare("-dump") == 0) {
			if(++i<argc)
				dumpfile = argv[i];
			else
				usage_err(temp);
		} else
			usage_err(temp);
	}
	Game *game = new Game();
	game->setDebug(debug);
	Agent *agent = new Agent(game);
	agent->setDebug(debug);

	for(int i=0; i<gameCounter; i++) {
		if(debug) cout<<"Running Trial: "<<i<<endl;
		game->Reset();
		if(debug) game->Eval();
		while(game->Status()) {
			//game->Eval();
			Action move = agent->Move();
			if(debug) cout<<"\tTaking Action: "<<move<<endl;
			game->Move(move);
		}
		game->Dealer();
		if(debug) game->Eval();
		agent->Update();
	}
	agent->DumpPolicy(dumpfile);
	return 0;
}

void usage_err(string key) {
	if(key.compare("-h") != 0)
		cout<<"Improper usage of "<<key<<endl;
	cout<<"Usage: ./blackjack [-g episode] [-dump file] [-debug]"<<endl;
	cout<<"./blackjack -h displays usage"<<endl;
	cout<<"View README for info"<<endl;
	exit(0);
}
