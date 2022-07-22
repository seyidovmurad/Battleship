#include "Header.h"

#define Green 2
#define Red 4
#define White 7

void printTable(const char table[][11]) {
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if (table[i][j] == 'X') {
				SetConsoleTextAttribute(handle, Red);
			}
			else if (table[i][j] == 'O') {
				SetConsoleTextAttribute(handle, Green);
			}
			cout << table[i][j] << " ";
			SetConsoleTextAttribute(handle, White);
		}
		cout << endl;
	}
}

void creatTable(char table[][11]) {
	int letter = 65;
	int num = 48;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			if ((i == 0 || j == 0) && !(i == 0 && j == 0)) {
				if (i == 0) {
					table[i][j] = num;
					num++;
				}
				else if (j == 0) {
					table[i][j] = letter;
					letter++;
				}
			}
			else {
				if (i == 0 && j == 0) {
					table[i][j] = ' ';
				}else
					table[i][j] = 45;// 45 is '-' in ASCII table
			}
		}
	}
}

bool isGameContinue(char table[][11]) {
	int count = 0;
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			if(table[i][j] == char(254))
				count++;
		}
	}
	if (count)
		return true;
	else {
		system("cls");
		cout << "\n--------Bot Win--------\n";
		Sleep(2000);
		return false;
	}
}
bool isGameContinue(char table[][10]) {
	int count = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (table[i][j] == char(254))
				count++;
		}
	}
	if (count)
		return true;
	else {
		system("cls");
		cout << "\n--------Player Win--------\n";
		Sleep(2000);
		return false;
	}
}