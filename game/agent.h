//=================================
// include guard
#ifndef __AGENT_H_INCLUDED__
#define __AGENT_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Agent {
	
	Game* game;
	bool debug;
	double qval[10][10][2][2]; // player sum, dealer showing, usable ace, HIT / STAY
	int visit[10][10][2][2]; // player sum, dealer showing, usable ace, HIT / STAY

	public:
		Agent( Game*);
		void setDebug( bool x ) { debug = x; };
		Action Move();
		void Update();
		void DumpPolicy(string file);
};

//=================================
// end guard
#endif
//=================================
