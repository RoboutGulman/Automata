#pragma once
#include "Automates.h"

template <typename Map>
bool MapsAreEqual(Map const& lhs, Map const& rhs)
{
	return lhs.size() == rhs.size()
		&& std::equal(lhs.begin(), lhs.end(), rhs.begin(),
			[](auto a, auto b) { return a.first == b.first && a.second == b.second; });
}

struct TemporaryAutomataInfo
{
	int groupsNumber = 0;
	map<int, int> stateIndexToGroup;
	bool operator!=(TemporaryAutomataInfo const& other) const
	{
		return groupsNumber != other.groupsNumber
			|| !MapsAreEqual(stateIndexToGroup, other.stateIndexToGroup);
	}
};

TemporaryAutomataInfo OneStep(const vector<vector<int>> statesTransitions, const TemporaryAutomataInfo& temp)
{
	TemporaryAutomataInfo result;
	vector<vector<int>> tempStatesTrans;

	for (auto stateTransitions : statesTransitions)
	{
		vector<int> tempTrans;
		for (auto transition : stateTransitions)
		{
			tempTrans.push_back(temp.stateIndexToGroup.find(transition)->second);
		}
		tempStatesTrans.push_back(tempTrans);
	}

	for (int i = 1; i <= temp.groupsNumber; i++)
	{
		set<int> statesIndexes;
		for (auto it = temp.stateIndexToGroup.begin(); it != temp.stateIndexToGroup.end(); it++)
		{
			if (it->second == i)
			{
				statesIndexes.insert(it->first);
			}
		}
		map<vector<int>, int> uniqueTransitionsToNewGroups;
		for (int j = 0; j < tempStatesTrans.size(); j++)
		{
			if (statesIndexes.find(j) == statesIndexes.end())
			{
				continue;
			}
			if (!uniqueTransitionsToNewGroups[tempStatesTrans[j]])
			{
				result.groupsNumber++;
				uniqueTransitionsToNewGroups[tempStatesTrans[j]] = result.groupsNumber;
			}
			result.stateIndexToGroup[j] = uniqueTransitionsToNewGroups[tempStatesTrans[j]];
		}
	}
	return result;
}

template <typename T>
Automata<T> DeleteUnvisitedStates(const Automata<T>& automata)
{
	Automata<T> result = automata;
	set<int> indexesOfVisitedStates;
	for (auto state : automata.states)
	{
		for (auto transition : state.transitions)
		{
			if (state.index != transition)
			{
				indexesOfVisitedStates.insert(transition);
			}
		}
	}
	
	for (int i = 1; i < automata.states.size(); i++)
	{
		if (indexesOfVisitedStates.find(i) == indexesOfVisitedStates.end())
		{
			result.stateNames.erase(result.stateNames.begin() + i);
			result.states.erase(result.states.begin()+i);
		}
	}
	return result;
}

template <typename T>
Automata<T> MinimizeAutomata(const Automata<T>& automata)
{
	Automata<T> automataWithoutUnvisitedStates = DeleteUnvisitedStates<T>(automata);
	Automata<T> result;
	TemporaryAutomataInfo newTempAut;
	map<T, int> outputsToGroup;
	vector<vector<int>> statesTransitions;

	for (auto state : automataWithoutUnvisitedStates.states)
	{
		if (!outputsToGroup[state.output])
		{
			newTempAut.groupsNumber++;
			outputsToGroup[state.output] = newTempAut.groupsNumber;
		}

		statesTransitions.push_back(state.transitions);
		newTempAut.stateIndexToGroup[state.index] = outputsToGroup[state.output];
	}

	TemporaryAutomataInfo oldTempAut;

	while (oldTempAut != newTempAut)
	{
		oldTempAut = newTempAut;
		newTempAut = OneStep(statesTransitions, oldTempAut);
	}

	for (int i = 1; i <= newTempAut.groupsNumber; i++)
	{
		for (auto it = newTempAut.stateIndexToGroup.begin(); it != newTempAut.stateIndexToGroup.end(); it++)
		{
			if (it->second == i)
			{
				AutomataState<T> state;
				state.index = it->first;
				state.output = automataWithoutUnvisitedStates.states[state.index].output;
				vector<int> transitions;
				for (auto transition : automataWithoutUnvisitedStates.states[state.index].transitions)
				{
					transitions.push_back(newTempAut.stateIndexToGroup.find(transition)->second - 1);
				}
				state.transitions = transitions;
				result.states.push_back(state);
				break;
			}
		}
	}
	for (int i = 1; i <= result.states.size(); i++)
	{
		string newStateName = "S" + to_string(i);
		result.stateNames.push_back(newStateName);
	}
	result.inputAlphabet = automataWithoutUnvisitedStates.inputAlphabet;
	return result;
}
