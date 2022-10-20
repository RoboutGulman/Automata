#include "stdafx.h"

#include "InputAndOutput.h"
#include "Minimization.h"

using namespace std;

struct Args
{
	string AutomataType;
	string InputFile;
	string OutputFile;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n";
		return nullopt;
	}
	Args args;
	args.AutomataType = argv[1];
	args.InputFile = argv[2];
	args.OutputFile = argv[3];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	if (args->AutomataType == "mealy")
	{
		auto mealy = ReadMealy(args->InputFile);
		auto minimizedMealy = MinimizeAutomata<MealyAutomata, MealyState, vector<string>>(mealy); // MinimizeMealyAutomata(mealy);
		WriteMealyToFile(minimizedMealy, args->OutputFile);
		return 0;
	}
	if (args->AutomataType == "moore")
	{
		auto moore = ReadMoore(args->InputFile);
		auto minimizedMoore = MinimizeAutomata<MooreAutomata, MooreState, string>(moore);
		//MinimizeMooreAutomata(moore);
		WriteMooreToFile(minimizedMoore, args->OutputFile);
		return 0;
	}
	return 1;
}