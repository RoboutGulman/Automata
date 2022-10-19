#pragma once
#include "stdafx.h"

using namespace std;

struct MooreState
{
	int index;
	string output;
	vector<int> transitions;
	bool operator==(MooreState const& other) const
	{
		return (index == other.index);
	}
};

struct MooreAutomata
{
	vector<string> inputAlphabet;
	vector<string> stateNames;
	vector<MooreState> states;
};

struct MealyAutomata
{
	vector<string> states;
	vector<string> inputAlphabet;
	vector<vector<pair<int, string>>> transitionTable;
};
