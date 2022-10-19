#include "stdafx.h"

#include "InputAndOutput.h"
#include "Transform.h"

using namespace std;

struct Args
{
    string TransitType;
    string InputFile;
    string OutputFile;
};

optional<Args> ParseArgs(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Invalid arguments count\n";
        return nullopt;
    }
    Args args;
    args.TransitType = argv[1];
    args.InputFile = argv[2];
    args.OutputFile = argv[3];
    return args;
}

int main(int argc, char *argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    if (args->TransitType == "mealy-to-moore")
    {
        auto mealy = ReadMealy(args->InputFile);
        auto moore = TransformMealyToMoore(mealy);
        WriteMooreToFile(moore, args->OutputFile);
        return 0;
    }
    if (args->TransitType == "moore-to-mealy")
    {
        auto moore = ReadMoore(args->InputFile);
        auto mealy = TransformMooreToMealy(moore);
        WriteMealyToFile(mealy, args->OutputFile);
        return 0;
    }
    return 1;
}
