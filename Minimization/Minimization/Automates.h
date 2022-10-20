#pragma once
#include "stdafx.h"

using namespace std;

struct MooreState
{
	int index;
	string output;
	vector<int> transitions;
};

struct MealyState
{
	int index;
	vector<string> output;
	vector<int> transitions;
};

struct MooreAutomata
{
	vector<string> inputAlphabet;
	vector<string> stateNames;
	vector<MooreState> states;
};

struct MealyAutomata
{
	vector<string> inputAlphabet;
	vector<string> stateNames;
	vector<MealyState> states;
};
