#include "stdafx.h"

#include "Transform.h"

using namespace std;

MealyAutomata TransformMooreToMealy(const MooreAutomata &moore)
{
    MealyAutomata result;
    for (auto row : moore.transitionTable)
    {
        vector<pair<int, string>> mealyRow;
        for (auto point : row)
        {
            mealyRow.push_back(make_pair(point, moore.statesOutputs[point]));
        }
        result.transitionTable.push_back(mealyRow);
    }
    result.inputAlphabet = moore.inputAlphabet;
    result.states = moore.states;
    return result;
}

MooreAutomata TransformMealyToMoore(const MealyAutomata &mealy)
{
    int count = 0;
    map<pair<int, string>, int> newStates;

    for (auto str : mealy.transitionTable)
    {
        for (auto p : str)
            if (newStates.find(p) == newStates.end())
            {
                count++;
                newStates[p] = count;
            }
    }

    MooreAutomata moore(newStates.size());
    moore.inputAlphabet = mealy.inputAlphabet;
    moore.states = mealy.states;
    for (auto state : newStates)
    {
        moore.statesOutputs[state.second - 1] = state.first.second;
    }

    for (auto mealyRow : mealy.transitionTable)
    {
        vector<int> stroke(newStates.size(), 0);

        for (auto state : newStates)
        {
            stroke[state.second - 1] = newStates[mealyRow[state.first.first]];
        }

        moore.transitionTable.push_back(stroke);
    }

    return moore;
}
