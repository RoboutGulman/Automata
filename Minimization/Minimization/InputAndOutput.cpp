#include "stdafx.h"

#include "InputAndOutput.h"

using namespace std;

bool GetLineWithoutFirst(ifstream& input, vector<string>& result, vector<string>& inputAlphabet,
	bool firstElementToAlphabet = false)
{
	result.clear();
	string buffer;
	if (getline(input, buffer))
	{
		boost::algorithm::split(result, buffer, boost::is_any_of(";"));
		if (firstElementToAlphabet)
		{
			inputAlphabet.push_back(result[0]);
		}
		result.erase(result.begin());
		return true;
	}
	return false;
}

vector<vector<string>> ReadFileAsMatrix(const string& inputFileName)
{
	ifstream input;
	input.open(inputFileName);

	vector<string> str;
	string buffer;
	getline(input, buffer);
	boost::algorithm::split(str, buffer, boost::is_any_of(";"));

	vector<vector<string>> result(str.size());
	for (int i = 0; i < str.size(); i++)
	{
		result[i].push_back(str[i]);
	}

	while (getline(input, buffer))
	{
		boost::algorithm::split(str, buffer, boost::is_any_of(";"));
		for (int i = 0; i < str.size(); i++)
		{
			result[i].push_back(str[i]);
		}
	}
	return result;
}

map<string, int> GetIndexedMapForVector(const vector<string>& vector)
{
	map<string, int> result;
	for (auto item : vector)
	{
		auto iter = std::find(vector.begin(), vector.end(), item);
		int index = std::distance(vector.begin(), iter);
		result[item] = index;
	}
	return result;
}

MooreAutomata ReadMoore(const string& inputFileName)
{
	vector<vector<string>> matrix = ReadFileAsMatrix(inputFileName);

	MooreAutomata moore;
	matrix[0].erase(matrix[0].begin(), matrix[0].begin() + 2);

	for (int i = 1; i < matrix.size(); i++)
	{
		moore.stateNames.push_back(matrix[i][1]);
	}

	map<string, int> stateNameToIndex = GetIndexedMapForVector(moore.stateNames);

	moore.inputAlphabet = matrix[0];

	for (int i = 1; i < matrix.size(); i++)
	{
		MooreState state;
		state.index = i - 1;
		state.output = matrix[i][0];
		matrix[i].erase(matrix[i].begin(), matrix[i].begin() + 2);
		for (auto transition : matrix[i])
		{
			state.transitions.push_back(stateNameToIndex[transition]);
		}
		moore.states.push_back(state);
	}

	return moore;
}

MealyAutomata ReadMealy(const string& inputFileName)
{
	MealyAutomata mealy;
	ifstream input;
	input.open(inputFileName);
	vector<string> str;
	GetLineWithoutFirst(input, mealy.states, str);

	while (GetLineWithoutFirst(input, str, mealy.inputAlphabet, true))
	{
		vector<pair<int, string>> result;

		for (auto point : str)
		{
			vector<string> vec;
			pair<int, string> p;
			boost::algorithm::split(vec, point, boost::is_any_of("/"));
			auto iter = std::find(mealy.states.begin(), mealy.states.end(), vec[0]);
			size_t index = std::distance(mealy.states.begin(), iter);
			p = make_pair(index, vec[1]);
			result.push_back(p);
		}
		mealy.transitionTable.push_back(result);
	}
	return mealy;
}

void PrintVector(ofstream& output, const vector<string>& vec)
{
	for (auto str : vec)
	{
		output << ';' << str;
	}
	output << endl;
}

void WriteMealyToFile(const MealyAutomata& mealy, const string& outputFileName)
{
	std::ofstream output;
	output.open(outputFileName);
	PrintVector(output, mealy.states);
	int count = 0;
	for (auto row : mealy.transitionTable)
	{
		output << mealy.inputAlphabet[count];
		count++;
		for (auto p : row)
		{
			output << ';' << mealy.states[p.first] << '/' << p.second;
		}
		output << endl;
	}
}

void WriteMooreToFile(const MooreAutomata& moore, const string& outputFileName)
{
	std::ofstream output;
	output.open(outputFileName);

	vector<string> outputs;
	for (auto state : moore.states)
	{
		outputs.push_back(state.output);
	}
	PrintVector(output, outputs);

	PrintVector(output, moore.stateNames);

	for (int i = 0; i < moore.inputAlphabet.size(); i++)
	{
		vector<string> transitionsOnThatSymb;
		for (auto state : moore.states)
		{
			string stateName = moore.stateNames[state.transitions[i] - 1];
			transitionsOnThatSymb.push_back(stateName);
		}
		output << moore.inputAlphabet[i];
		PrintVector(output, transitionsOnThatSymb);
	}
}
