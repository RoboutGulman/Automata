#pragma once
#include "stdafx.h"

#include "Automates.h"

using namespace std;

using mooreType = TypeSelector<AutomataType::Moore>::type;
using mealyType = TypeSelector<AutomataType::Mealy>::type;

Automata<mooreType> ReadMooreAutomata(const string& inputFileName);
Automata<mealyType> ReadMealyAutomata(const string& inputFileName);
void WriteMealyToFile(const Automata<mealyType>& mealy, const string& outputFileName);
void WriteMooreToFile(const Automata<mooreType>& moore, const string& outputFileName);
