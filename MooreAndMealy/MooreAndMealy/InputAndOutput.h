#pragma once
#include "stdafx.h"

#include "Transform.h"

using namespace std;

MooreAutomata ReadMoore(const string &inputFileName);
MealyAutomata ReadMealy(const string &inputFileName);
void WriteMealyToFile(const MealyAutomata &mealy, const string &outputFileName);
void WriteMooreToFile(const MooreAutomata &moore, const string &outputFileName);