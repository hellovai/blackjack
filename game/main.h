//=================================
// include guard
#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__
//=================================

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum Card {EMTPY, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, FACE };
enum Action {STAY, HIT, BUST};

typedef struct stateactionstruct
{
	int sum;
	Action action;
	bool ace;
	stateactionstruct(int xsum, bool xace, Action taken) : sum(xsum), ace(xace), action(taken) { };
	stateactionstruct() {};
} stateaction;

void usage_err(string key);


//=================================
// end guard
#endif
//=================================
