#include "Casino.h"
#pragma once
namespace S02239776 {


class TicTacToeGameKMF : public CSC2034::Casino
{
	

public:
	 TicTacToeGameKMF();

	void start();

	static TicTacToeGameKMF* makeGame();

private:

	void playGame();
	int getXCoord(int x);
	int getYCoord(int y);
	bool placeMarker(int x, int y, char currentPlayer);

	bool checkForVictory(char currentPlayer);

	//Clears the board
	void clearBoard();
	//Prints the board
	void printBoard();

	char board[3][3];

	};
	}

