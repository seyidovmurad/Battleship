#include "Header.h"

void setPlayerShip(char table[][11], Ship ship) {
	int col = 0;
	int row = ship.row + 1;
	int size = ship.size;
	if (ship.col < 75)
		col = int(ship.col) - 64;
	else
		col = int(ship.col) - 96;
	switch (ship.dir)
	{
	case 'v': 
		while (size) {
			table[col][row] = 254;
			col++;
			size--;
		}
		break;
	case 'h':
		while (size) {
			table[col][row] = 254;
			row++;
			size--;
		}
		break;
	case 'o':
		table[col][row] = 254;
	}
}

bool playerAim(char bot[][10], char player[][11], int row, char col) {
	int rowI = row + 1;
	int colI = 0;
	if ((row >= 0 && row <= 9) && ((col > 64 && col < 75) || (col > 96 && col < 107))) {
		if (col < 75)
			colI = int(col) - 64;
		else
			colI = int(col) - 96;
		if (player[colI][rowI] != 'X' && player[colI][rowI] != 'O') {
			if (bot[colI - 1][rowI - 1] == char(254)) {
				player[colI][rowI] = 'X';
				bot[colI - 1][rowI - 1] = 'X';
				return true;
			}
			else {
				player[colI][rowI] = 'O';
				bot[colI - 1][rowI - 1] = 'O';
				return false;
			}
		} else { cout << "\nError"; Sleep(500); }
	} else { cout << "\nError"; Sleep(500); }
	return true;
}


bool isAllCorrect(const char table[][11], Ship ship) {
	int col = 0;
	int row = ship.row + 1;
	int size = ship.size;
	if (ship.row >= 0 && ship.row <= 9 && ship.size > -1 && ship.size < 5) {
		if ((ship.col > 64 && ship.col < 75) || (ship.col > 96 && ship.col < 107)) {
			if (ship.col < 75)
				col = int(ship.col) - 64;
			else
				col = int(ship.col) - 96;
		}
		else
			return false;
	}
	else
		return false;
	if (table[col][row] != char(254)) {
		switch (ship.dir) {
		case 'v':
			if (col + size < 12) {
				while (size) {
					for (int i = col - 1; i < col + 2; i++) {
						for (int j = row - 1; j < row + 2; j++) {
							if (table[i][j] == char(254))
								return false;
						}
					}
					col++;
					size--;
				}
			}
			else return false; break;
		case 'h':
			if (row + size < 12) {
				while (size) {
					for (int i = col - 1; i < col + 2; i++) {
						for (int j = row - 1; j < row + 2; j++) {
							if (table[i][j] == char(254))
								return false;
						}
					}
					row++;
					size--;
				}
			}
			else return false; break;
		case 'o':
			for (int i = col - 1; i < col + 2; i++) {
				for (int j = row - 1; j < row + 2; j++) {
					if (table[i][j] == char(254))
						return false;
				}
			}break;
		default: return false;
			break;
		}
	}
	return true;
}