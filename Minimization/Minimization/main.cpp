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
		using type = TypeSelector<AutomataType::Mealy>::type;
		auto mealy = ReadMealyAutomata(args->InputFile);
		auto minimizedMealy = MinimizeAutomata<type>(mealy);
		WriteMealyToFile(minimizedMealy, args->OutputFile);
		return 0;
	}
	if (args->AutomataType == "moore")
	{
		using type = TypeSelector<AutomataType::Moore>::type;
		auto moore = ReadMooreAutomata(args->InputFile);
		auto minimizedMoore = MinimizeAutomata<type>(moore);
		WriteMooreToFile(minimizedMoore, args->OutputFile);
		return 0;
	}
	return 1;
}
