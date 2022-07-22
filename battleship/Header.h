#pragma once
#include <iostream>
#include <Windows.h>
#include <time.h> 

using namespace std;
struct Ship {
	short size;
	short row;
	char col;
	int colI;
	char dir;
};

//Function of Table
void creatTable(char table[][11]);//create player table
void printTable(const char table[][11]);//print player table
bool isGameContinue(char table[][11]);//check for winner-player
bool isGameContinue(char table[][10]);//check for winner-bot

//Function of Player
void setPlayerShip(char table[][11],Ship ship);//set player's ships
bool playerAim(char bot[][10], char player[][11], int row, char col);//Player attack to bot
bool isAllCorrect(const char table[][11], Ship ship);//check if ship can fit-player

//Function of Bot
void setBotShip(char table[][10]);//set bot'ships
bool botAim(char bot[][10],char player[][11]);//Bot attack to player
bool isAllCorrectBot(char bot[][10], Ship ship);//check if ship can fit-bot
void fillSpace(char bot[][10], char player[][11], int col, int row);

