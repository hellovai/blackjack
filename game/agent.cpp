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
	for(int k = 0; k < 2; k++) {
		qval[i][j][k][STAY] = 1;
		visit[i][j][k][STAY] = 0;
		qval[i][j][k][HIT] = 1;
		visit[i][j][k][HIT] = 0;
	}

	for(int i = 0; i < 10; i++)
	for(int j = 0; j < 10; j++)
	for(int k = 0; k < 2; k++)
		policy[i][j][k] = (i > 7 ? true : false);
}

Action Agent::Move() {
	int id = 0;
	if(game->Ace()) id = 1; 
	bool state = policy[game->Sum() - 12][game->Revealed()-1][id];
	if(state) {
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
				cout<<sa[i].sum<<" "<<dealer<<" "<<(sa[i].ace == 1 ? "Useable Ace" : "No Useable Ace")<<endl;
				cout<<"\tQVal: "<<q<<" Visits: "<<v<<endl;
			}
			//q += (double) result / (double) ++v;
			q = (v == 0 ? q : q * (double) v) + (double) result;
			v++;
			q /= (double) v;
			qval[sa[i].sum-12][dealer][ace][sa[i].action] = q;
			visit[sa[i].sum-12][dealer][ace][sa[i].action] = v;
			if(debug)
				cout<<"\tFinal->QVal: "<<q<<" Visits: "<<v<<endl;
		} else {
			if(debug) cout<<"Bust!"<<endl;
		}
	}

	for(int i = 0; i < 10; i++)
	for(int j = 0; j < 10; j++)
	for(int k = 0; k < 2; k++)
		if(qval[i][j][k][STAY] < qval[i][j][k][HIT])
			policy[i][j][k] = false;
		else if(qval[i][j][k][STAY] > qval[i][j][k][HIT])
			policy[i][j][k] = true;
	//cout<<"Done Updating"<<endl;
}

void Agent::DumpPolicy(string name) {
	string file = name;
	file.append("-usable.dat");
	ofstream myfile, pol;
	myfile.open (file.c_str());
	file.append("pol");
	pol.open(file.c_str());
	myfile<<"Usable Ace"<<endl;
	int index = 1;
	for(int i=0; i < 10; i ++)
	for(int j=0; j < 10; j ++){
		myfile<<i<<" "<<j<<" "<<(policy[i][j][index] ? qval[i][j][index][STAY] :  qval[i][j][index][HIT])<<endl;
		pol<<i<<" "<<j<<" "<<policy[i][j][index]<<endl;
	}
	myfile.close();
	pol.close();
	file = name;
	file.append("-no-usable.dat");
	myfile.open(file.c_str());
	file.append("pol");
	pol.open(file.c_str());
	myfile<<"No Usable Ace"<<endl;
	index = 0;
	for(int i=0; i < 10; i ++)
	for(int j=0; j < 10; j ++) {
		myfile<<i<<" "<<j<<" "<<(policy[i][j][index] ? qval[i][j][index][STAY] :  qval[i][j][index][HIT])<<endl;;
		pol<<i<<" "<<j<<" "<<policy[i][j][index]<<endl;
	}
	myfile.close();
	pol.close();
	file = name;
	file.append("-visit.dat");
	myfile.open(file.c_str());
	myfile<<"Usable Ace"<<endl;
	index = 1;
	for(int i=0; i < 10; i ++)
	for(int j=0; j < 10; j ++) {
		myfile<<i<<" "<<j<<" "<< visit[i][j][index][STAY] <<"-"<<qval[i][j][index][STAY]<<" "<<visit[i][j][index][HIT] <<"-"<<qval[i][j][index][HIT]<<endl;
	}
	myfile.close();
}