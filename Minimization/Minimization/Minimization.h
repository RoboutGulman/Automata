#pragma once
#include "Automates.h"

MooreAutomata MinimizeMooreAutomata(const MooreAutomata& moore);
MealyAutomata MinimizeMealyAutomata(const MealyAutomata& mealy);

<template T> T MinimizeAutomata(const T& automata);
