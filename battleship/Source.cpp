#include <iostream>
#include "Header.h"

using namespace std;
int main() {
	srand(time(NULL));
	//Variable
	Ship ship;
	bool isGameOn = true;
	int sum = 0; // Summary of all player ship
	int numOfShip[]{ 5,4,3,2 };//Number of ship { x1,x2,x3,x4 }5,4,3,2 
	//Array of player and bot 
	char playerAimTable[11][11];
	char playerShipTable[11][11];
	char botAimTable[10][10]{};
	char botShipTable[10][10]{};
	//Creating Player's Table
	creatTable(playerAimTable);
	creatTable(playerShipTable);
	//Setting bot's ship
	setBotShip(botShipTable);
	for (int i = 0; i < 4; i++) 
		sum += numOfShip[i];
	//Setting player's ship
	while (sum) {
		printTable(playerShipTable);
		for (int i = 0; i < 4; i++)	{
			if (numOfShip[i])
				cout << "Ship x" << i + 1 << " => " << numOfShip[i] << endl;//Print remaining ships
		}
		//Ask ships specs v1
		cout << "Ship: Size, Coordinate(col,row), Direction(v-Down,h-Right) \nInput: ";
		cin >> ship.size >> ship.col >> ship.row >> ship.dir;
		if (ship.size == 1) ship.dir = 'o';
		//Ask ships specs v2
		/*cout << "\nSetting Player ships\n";
		cout << "Size of ship: ";
		cin >> ship.size;
		if (ship.size > 1) {
			cout << "Direction of Ship(h-hor,v-ver): ";
			cin >> ship.dir;
		}
		else ship.dir = 'o';
		cout << "Coordinate\n";
		cout << "Col(only letter): ^ ";
		cin >> ship.col;
		cout << "Row(only number): > ";
		cin >> ship.row;*/
		bool isItCorrect = isAllCorrect(playerShipTable, ship);
		if (isItCorrect && numOfShip[ship.size - 1]) { // if all data is correct
			numOfShip[ship.size - 1]--;
			sum--;
			setPlayerShip(playerShipTable, ship);
		}
		else {
			Sleep(500);
			system("cls");
			cout << "\nError: Please pay attention!";
			Sleep(700);
		}
		system("cls");
	}
	//Game Start 
	while (isGameOn) {
		bool didItHit = true;
		//Print Table
		printTable(playerAimTable);
		cout << "\n\n";
		printTable(playerShipTable);
		//Bot Attack
		while (didItHit && isGameOn) {//if it hits bot continue
			didItHit = botAim(botAimTable, playerShipTable);
			system("cls");
			printTable(playerAimTable);
			cout << "\n\n";
			printTable(playerShipTable);
		}
		isGameOn = isGameContinue(playerShipTable);
		//Player Attack
		didItHit = true;
		if (isGameOn) {
			while (didItHit && isGameOn) {//if it hits player continue
				int row; char col;
				cout << endl << "Coordinate: ";
				cin >> col >> row;
				//Player Fire
				didItHit = playerAim(botShipTable, playerAimTable, row, col);
				system("cls");
				printTable(playerAimTable);
				cout << "\n\n";
				printTable(playerShipTable);
			}
			isGameOn = isGameContinue(botShipTable);
			system("cls");
		}
	}
}