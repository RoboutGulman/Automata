#pragma once
#include "stdafx.h"

using namespace std;

enum class AutomataType
{
	Mealy,
	Moore
};

template <AutomataType TYPE>
struct TypeSelector
{
	using type = string;
};

template <>
struct TypeSelector<AutomataType::Mealy>
{
	using type = vector<string>;
};

template <>
struct TypeSelector<AutomataType::Moore>
{
	using type = string;
};

template <typename T>
class AutomataState
{
public:
	int index;
	T output;
	vector<int> transitions;
};

template <typename T>
class Automata
{
public:
	vector<string> inputAlphabet;
	vector<string> stateNames;
	vector<AutomataState<T>> states;
};