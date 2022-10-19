#include "stdafx.h"

#include "InputAndOutput.h"
#include "Transform.h"

using namespace std;

bool GetLineWithoutFirst(ifstream &input, vector<string> &result, vector<string> &inputAlphabet,
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

MooreAutomata ReadMoore(const string &inputFileName)
{
    MooreAutomata moore;
    ifstream input;
    input.open(inputFileName);
    vector<string> str;
    GetLineWithoutFirst(input, moore.statesOutputs, str);
    GetLineWithoutFirst(input, moore.states, str);
    while (GetLineWithoutFirst(input, str, moore.inputAlphabet, true))
    {
        vector<int> result;
        for (auto point : str)
        {
            auto iter = std::find(moore.states.begin(), moore.states.end(), point);
            size_t index = std::distance(moore.states.begin(), iter);
            result.push_back(index);
        }
        moore.transitionTable.push_back(result);
    }
    return moore;
}

MealyAutomata ReadMealy(const string &inputFileName)
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

void PrintVector(ofstream &output, const vector<string> &vec)
{
    for (auto str : vec)
    {
        output << ';' << str;
    }
    output << endl;
}

void WriteMealyToFile(const MealyAutomata &mealy, const string &outputFileName)
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

void WriteMooreToFile(const MooreAutomata &moore, const string &outputFileName)
{
    std::ofstream output;
    output.open(outputFileName);
    PrintVector(output, moore.statesOutputs);
    for (int i = 0; i < moore.statesOutputs.size(); i++)
    {
        output << ';' << 'S' << i + 1;
    }
    output << endl;
    int counter = 0;
    for (auto stroke : moore.transitionTable)
    {
        output << moore.inputAlphabet[counter];
        counter++;
        for (auto number : stroke)
        {
            output << ';' << 'S' << number;
        }
        output << endl;
    }
}
