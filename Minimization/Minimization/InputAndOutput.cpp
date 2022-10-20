#include "stdafx.h"

#include "InputAndOutput.h"

using namespace std;

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
	moore.inputAlphabet = matrix[0];

	for (int i = 1; i < matrix.size(); i++)
	{
		moore.stateNames.push_back(matrix[i][1]);
	}
	map<string, int> stateNameToIndex = GetIndexedMapForVector(moore.stateNames);

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
	vector<vector<string>> matrix = ReadFileAsMatrix(inputFileName);

	MealyAutomata mealy;

	matrix[0].erase(matrix[0].begin());
	mealy.inputAlphabet = matrix[0];

	for (int i = 1; i < matrix.size(); i++)
	{
		mealy.stateNames.push_back(matrix[i][0]);
	}
	map<string, int> stateNameToIndex = GetIndexedMapForVector(mealy.stateNames);

	for (int i = 1; i < matrix.size(); i++)
	{
		MealyState state;
		state.index = i - 1;
		matrix[i].erase(matrix[i].begin());
		for (auto transition : matrix[i])
		{
			vector<string> vec;
			boost::algorithm::split(vec, transition, boost::is_any_of("/"));
			state.transitions.push_back(stateNameToIndex[vec[0]]);
			state.output.push_back(vec[1]);
		}
		mealy.states.push_back(state);
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
	PrintVector(output, mealy.stateNames);

	for (int i = 0; i < mealy.inputAlphabet.size(); i++)
	{
		vector<string> transitionsOnThatSymb;
		for (auto state : mealy.states)
		{
			string stateNameAndOutput = mealy.stateNames[state.transitions[i]] + '/' + state.output[i];
			transitionsOnThatSymb.push_back(stateNameAndOutput);
		}
		output << mealy.inputAlphabet[i];
		PrintVector(output, transitionsOnThatSymb);
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
			string stateName = moore.stateNames[state.transitions[i]];
			transitionsOnThatSymb.push_back(stateName);
		}
		output << moore.inputAlphabet[i];
		PrintVector(output, transitionsOnThatSymb);
	}
}
