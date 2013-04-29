#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib> 

#include "main.h"
#include "game.h"
#include "agent.h"

using namespace std;
Agent::Agent( Game* gmptr) {
	game = gmptr;
	debug = false;
	for(int i = 0; i < 10; i++)
	for(int j = 0; j < 10; j++)
	for(int k = 0; k < 2; k++)
	for(int l = 0; l < 2; l++) {
		qval[i][j][j][l] = 0.0;
		visit[i][j][j][l] = 0;
		if(i > 7) {
			qval[i][j][j][0] = 1;
			qval[i][j][j][1] = -1;
		}
	}
}

Action Agent::Move() {
	double* state = qval[game->Sum() - 12][game->Revealed()][game->Ace()];
	if(state[0] > state[1]) {
		return STAY;
	} else
		return HIT;
}

void Agent::Update() {
	if(debug) cout<<"Updating Agent..."<<endl;
	vector<stateaction> sa = game->History();
	int dealer = game->Revealed() - 1;
	int result = game->Result();
	if(debug) cout<<"States to update: "<<sa.size()<<endl;
	for(int i = 0; i < (int) sa.size(); i++ ) {
		if(debug) cout<<"This state is: "<<sa[i].action<<" "<<sa[i].sum<<endl;
		if(sa[i].action != BUST) {
			int ace = sa[i].ace;
			if(debug) cout<<"qval["<<sa[i].sum-12<<"]["<<dealer<<"]["<<ace<<"]["<<sa[i].action<<"]"<<endl;
			double q = qval[sa[i].sum-12][dealer][ace][sa[i].action];
			int v = visit[sa[i].sum-12][dealer][ace][sa[i].action];
			if(debug) {
				cout<<sa[i].sum<<" "<<dealer<<" "<<(sa[i].ace ? "Useable Ace" : "No Useable Ace")<<endl;
				cout<<"\tQVal: "<<q<<" Visits: "<<v<<endl;
			}
			v++;
			q += (double) result/((double) v);
			qval[sa[i].sum-12][dealer][ace][sa[i].action] = q;
			visit[sa[i].sum-12][dealer][ace][sa[i].action] = v;
			if(debug)
				cout<<"\tFinal->QVal: "<<q<<" Visits: "<<v<<endl;
		} else {
			if(debug) cout<<"Bust!"<<endl;
		}
	} 
	//cout<<"Done Updating"<<endl;
}

void Agent::DumpPolicy(string name) {
  string file = name;
  file.append("-usable.dat");
  ofstream myfile;
  myfile.open (file.c_str());
  myfile<<"Usable Ace"<<endl;
  for(int i=0; i < 10; i ++)
  for(int j=0; j < 10; j ++)
  	myfile<<i+12<<" "<<j+1<<" "<<(qval[i][j][1][0] > qval[i][j][1][1] ? qval[i][j][1][0] :  qval[i][j][1][1])<<endl;
  myfile.close();
  file = name;
  file.append("-no-usable.dat");
  myfile.open(file.c_str());
  myfile<<"No Usable Ace"<<endl;
  for(int i=0; i < 10; i ++)
  for(int j=0; j < 10; j ++)
  	myfile<<i+12<<" "<<j+1<<" "<<(qval[i][j][0][0] > qval[i][j][0][1] ? qval[i][j][0][0] :  qval[i][j][0][1])<<endl;
  myfile.close();
}