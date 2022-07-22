#include "Header.h"

bool secTry = false;
int lastR, lastC = 0;
int counter = 1;
char dirct = 'v';
char hitDir = 'u';//u-up,d-down,l-left,r-right
bool botAim(char bot[][10], char player[][11]) {
	int col = 0, row = 0;
	bool hit = false;
	if(secTry) {
		switch (hitDir)	{
		case 'u':
			if (lastC - counter >= 0) {
				if (player[lastC - counter + 1][lastR + 1] == char(254)) {
					player[lastC - counter + 1][lastR + 1] = 'X';
					bot[lastC - counter][lastR] = 'X';
					counter++;
					fillSpace(bot, player, lastC - counter, lastR);
					hit = true;
				}
				else {
					if (bot[lastC - counter][lastR] != 'X') {
						bot[lastC - counter][lastR] = 'O';
						player[lastC - counter + 1][lastR + 1] = 'O';
					}
					hit = false;
					hitDir = 'd';
					counter = 1;
				}
				break;
			}
			else hitDir = 'd';
		case 'd':
			if (lastC + counter < 10) {
				if (player[lastC + counter + 1][lastR + 1] == char(254)) {
					player[lastC + counter + 1][lastR + 1] = 'X';
					bot[lastC + counter][lastR] = 'X';
					counter++;
					fillSpace(bot, player, lastC + counter, lastR);
					hit = true;
				}
				else {
					if (bot[lastC + counter][lastR] != 'X') {
						player[lastC + counter + 1][lastR + 1] = 'O';
						bot[lastC + counter][lastR] = 'O';
					}
					hit = false;
					secTry = false;
					hitDir = 'r';
					counter = 1;
				}
				break;
			}
			else { hitDir = 'r'; }
		case 'r':
			if (lastR + counter < 10) {
				if (player[lastC + 1][lastR + counter + 1] == char(254)) {
					player[lastC + 1][lastR + counter + 1] = 'X';
					bot[lastC][lastR + counter] = 'X';
					counter++;
					fillSpace(bot, player, lastC, lastR + counter);
					hit = true;
				}
				else {
					if (bot[lastC][lastR + counter] != 'X') {
						player[lastC + 1][lastR + counter + 1] = 'O';
						bot[lastC][lastR + counter] = 'O';
					}
					hit = false;
					hitDir = 'l';
					counter = 1;
				}
			break;
			}else hitDir = 'l';
		case 'l':
			if (lastR - counter >= 0) {
				if (player[lastC + 1][lastR - counter + 1] == char(254)) {
					player[lastC + 1][lastR - counter + 1] = 'X';
					bot[lastC][lastR - counter] = 'X';
					counter++;
					fillSpace(bot, player, lastC, lastR - counter);
					hit = true;
				}
				else {
					if (bot[lastC][lastR - counter] != 'X') {
						player[lastC + 1][lastR - counter + 1] = 'O';
						bot[lastC][lastR - counter] = 'O';
					}
					hit = false;
					secTry = false;
					counter = 1;
				}
			}
			else {
				hit = false;
				secTry = false;
			}
			break;
		}
	}	
	if (!secTry) {
		counter = 1;
		bool found = false;
		while (!found) {
			col = rand() % 10;
			row = rand() % 10;
			if (bot[col][row] != 'X' && bot[col][row] != 'O')
				found = true;
		}
		if (player[col + 1][row + 1] == char(254)) {
			bot[col][row] = 'X';
			player[col + 1][row + 1] = 'X';
			hit = true;
			fillSpace(bot, player, col, row);
			lastR = row;
			lastC = col;
			if(col>0)hitDir = 'u';
			else hitDir = 'd';
			secTry = true;
		}
		else {
			if (player[col+1][row+1] == char(45)) {
				bot[col][row] = 'O';
				player[col + 1][row + 1] = 'O';
			}
			hit = false;
		}
	}
	return hit;
}

void fillSpace(char bot[][10], char player[][11], int col, int row) {
	for (int i = col - 1; i < col + 2; i++) {
		for (int j = row - 1; j < row + 2; j++) {
			if (i != col && j != row && i >= 0 && i < 10 && j >= 0 && j < 10) {
				if (player[i+1][j+1] == char(45)) {
					bot[i][j] = 'O';
					player[i + 1][j + 1] = 'O';
				}
			}
		}
	}
}

void setBotShip(char bot[][10]) {
	bool shipSet = false;
	while (!shipSet) {
		shipSet = true;
		Ship ship;
		int ships[]{ 5,4,3,2 };
		int count = 0;
		int bug = 0;
		int size = 4;
		int col, row = 0;
		for (int i = 0; i < 4; i++)
			count += ships[i];
		while (count && shipSet) {
			while (ships[size - 1] && shipSet) {
				bool found = false;
				int size2 = size;
				while (!found && shipSet) {
					col = rand() % 10;
					row = rand() % 10;
					ship.colI = col;
					ship.row = row;
					ship.size = size;
					bug++;
					if (bug > 600) {
						shipSet = false;
					}
					if (isAllCorrectBot(bot, ship))
						found = true;
				}
				if (size == 1) {
					bot[col][row] = char(254);
					ships[size - 1]--;
					count--;
				}
				else {
					if (dirct == 'v') {
						while (size2) {
							bot[col][row] = 254;
							col++;
							size2--;
						}
						ships[size - 1]--;
						count--;
					}
					else if (dirct == 'h') {
						while (size2) {
							bot[col][row] = 254;
							row++;
							size2--;
						}
						ships[size - 1]--;
						count--;
					}
				}
			}
			size--;
		}
	}
}

bool isAllCorrectBot(char bot[][10], Ship ship) {
	int size = ship.size;
	int row = ship.row;
	int col = ship.colI;
	dirct = 'v';
	if (size == 1) {
		for (int i = col - 1; i < col + 2; i++) {
			for (int j = row - 1; j < row + 2; j++) {
				if (i >= 0 && i < 10 && j>= 0 && j < 10) {
					if (bot[i][j] == char(254))
						dirct = 'f';
				}
			}
		}
	}
	else {
		if (col + size < 11) {
			while (size) {
				for (int i = col - 1; i < col + 2; i++) {
					for (int j = row - 1; j < row + 2; j++) {
						if (i >= 0 && i < 10 && j >= 0 && j < 10) {
							if (bot[i][j] == char(254))
								dirct = 'h';
						}
					}
				}
				col++;
				size--;
			}
		}
		else dirct = 'h';
		if (dirct == 'h') {
			size = ship.size;
			row = ship.row;
			col = ship.colI;
			if (row + size < 11) {
				while (size) {
					for (int i = col - 1; i < col + 2; i++) {
						for (int j = row - 1; j < row + 2; j++) {
							if (i >= 0 && i < 10 && j >= 0 && j < 10) {
								if (bot[i][j] == char(254))
									dirct = 'f';
							}
						}
					}
					row++;
					size--;
				}
			}else dirct = 'f';
		}
	}
	if (dirct == 'f')
		return false;
	return true;
}