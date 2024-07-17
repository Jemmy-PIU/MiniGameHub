#include <iostream>
#include <string>
#pragma once
using namespace std;

struct PlayerData
{
    int id;
    string name;
    double balance;
    int totalGames, wins, losses, draws;
};

struct PlayerGameResultData
{
    int id;
    string name;
    string gameStatus;
    double initialBalance;
    double finalBalance;
};