#pragma once
#include "stdafx.h"

using namespace std;

struct MooreAutomata
{
	vector<string> states;
	vector<string> inputAlphabet;
	vector<string> statesOutputs;
	vector<vector<int>> transitionTable;
	MooreAutomata(size_t size = 0)
		: statesOutputs(size, "")
	{
	}
};

struct MealyAutomata
{
	vector<string> states;
	vector<string> inputAlphabet;
	vector<vector<pair<int, string>>> transitionTable;
};

MealyAutomata TransformMooreToMealy(const MooreAutomata& moore);
MooreAutomata TransformMealyToMoore(const MealyAutomata& mealy);
