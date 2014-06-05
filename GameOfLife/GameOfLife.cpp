#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;

bool MakeArray(string);

const int ROWS = 12;
const int COLS = 30;
const char LIVE = 'X';
const char DEAD = '.';

char gameField[ROWS][COLS];
char newBoard[ROWS][COLS];

//Prototypes
void update(char[][COLS]);
void switchBoards(char[][COLS]);
void GameBoard(char[][COLS]);

int main(){
	
	MakeArray("life.txt");
	while (true){
		update(gameField);
		GameBoard(gameField);
		switchBoards(gameField);
		Sleep(200);
		system("cls");
	}
		
	return 0;
}

void GameBoard(char board[][COLS])
{
	for (int y = 1; y <= ROWS - 2; y++)
	{
		for (int x = 1; x <= COLS - 2; x++)
		{
			cout << board[y][x];
		}
		cout << endl;
	}
	cout << endl;
}

bool MakeArray(string filename){

	ifstream myfile;
	myfile.open(filename.c_str());
	if (!myfile) return true;

	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			myfile >> gameField[y][x];
		}
	}
	myfile.close();

	return false;
}

void update(char board[][COLS])
{
	for (int y = 0; y < ROWS; y++){
		for (int x = 0; x < COLS; x++){
			int LiveCnt = 0;
			if (board[y - 1][x - 1] == LIVE){
				LiveCnt++;
			}
			if (board[y - 1][x] == LIVE){
				LiveCnt++;
			}
			if (board[y - 1][x + 1] == LIVE){
				LiveCnt++;
			}
			if (board[y][x - 1] == LIVE){
				LiveCnt++;
			}

			if (board[y][x + 1] == LIVE){
				LiveCnt++;
			}
			if (board[y + 1][x - 1] == LIVE){
				LiveCnt++;
			}
			if (board[y + 1][x + 1] == LIVE){
				LiveCnt++;
			}
			if (board[y + 1][x] == LIVE){
				LiveCnt++;
			}
			/*/
			Rules:
			1.	Any live cell with fewer than two live neighbours dies, as if caused by under-population.
			2.	Any live cell with two or three live neighbours lives on to the next generation.
			3.	Any live cell with more than three live neighbours dies, as if by overcrowding.
			4.	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
			/*/

			newBoard[y][x] = DEAD;

			if (board[y][x] == LIVE && LiveCnt < 2){ //rule 1
				newBoard[y][x] = DEAD;
			}
			else if (board[y][x] == LIVE && (LiveCnt == 2 || LiveCnt == 3)){ //rule 2
				newBoard[y][x] = LIVE;
			}
			else if (board[y][x] == LIVE && LiveCnt>3){ //rule 3
				newBoard[y][x] = DEAD;
			}
			else if (board[y][x] == DEAD && LiveCnt == 3){ //rule 4
				newBoard[y][x] = LIVE;
			}
		}
	}
}

void switchBoards(char board[][COLS]){
	for (int y = 0; y < ROWS; y++){
		for (int x = 0; x < COLS; x++){
			board[y][x] = newBoard[y][x];
		}
	}
}