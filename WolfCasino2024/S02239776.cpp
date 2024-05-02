#include "S02239776.h"
#include <iostream>

namespace S02239776 {


	 TicTacToeGameKMF::TicTacToeGameKMF() {

	}

		 TicTacToeGameKMF* TicTacToeGameKMF::makeGame() {
		return new TicTacToeGameKMF;
	}

	void TicTacToeGameKMF::start() {

		char input;
		bool isDone = false;
		 TicTacToeGameKMF game;

		while (isDone == false) {
			game.playGame();
			std::cout << "Would you like to play again? (Y/N): " << std::endl;
			std::cin >> input;
			if (input == 'N' || input == 'n') {
				isDone = true;
			}
		}

	}

	void TicTacToeGameKMF::playGame() {

		clearBoard();

		char player1 = 'X';
		char player2 = 'O';

		char currentPlayer = 'X';
		bool isDone = false;

		int x = 0;
		int y = 0;

		int turns = 0;

		while (isDone == false) {
			printBoard();
			x = getXCoord(x);
			y = getYCoord(y);

			if (placeMarker(x, y, currentPlayer) == false) {
				std::cout << "That spot has already been placed in" << std::endl;
			}
			else {

				turns++;
				if (checkForVictory(currentPlayer) == true) {
					std::cout << "Game is over " << currentPlayer << " won!!!";
					isDone = true;
				}
				else if (turns == 9) {
					std::cout << "Its a tie game!" << std::endl;
					isDone = true;
				}

				//Switches Players
				if (currentPlayer == player1) {
					currentPlayer = player2;
				}
				else {
					currentPlayer = player1;
				}
			}
		}
	}
	int TicTacToeGameKMF::getXCoord(int x) {

		bool isInputBad = true;

		while (isInputBad == true) {
			std::cout << "Enter the X coordinate" << std::endl;
			std::cin >> x;

			if (x < 1 || x > 3) {
				std::cout << "Invalid Coordinate!" << std::endl;
			}
			else {
				isInputBad = false;
			}

		}

		return x - 1;
	}

	int TicTacToeGameKMF::getYCoord(int y) {
		bool isInputBad = true;

		while (isInputBad == true) {
			std::cout << "Enter the Y coordinate" << std::endl;
			std::cin >> y;

			if (y < 1 || y > 3) {
				std::cout << "Invalid Coordinate!" << std::endl;
			}
			else {
				isInputBad = false;
			}

		}

		return y - 1;
	}
	bool TicTacToeGameKMF::placeMarker(int x, int y, char currentPlayer) {

		if (board[y][x] != ' ') {
			return false;
		}

		board[y][x] = currentPlayer;

		return true;
	}
	bool TicTacToeGameKMF::checkForVictory(char currentPlayer) {
		//Checking for three in a row 
		for (int i = 0; i < 3; i++) {
			if ((board[i][0] == currentPlayer) && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
				return true;
			}
		}
		//Checking for three in a colum 
		for (int i = 0; i < 3; i++) {
			if ((board[i][0] == currentPlayer) && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
				return true;
			}
		}
		// check top left diagonal
		if ((board[0][0] == currentPlayer) && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			return true;
		}
		// check top right diagonal
		if ((board[2][0] == currentPlayer) && board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
			return true;
		}
		return false;
	}

	void TicTacToeGameKMF::clearBoard()
	{

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = ' ';

			}
		}
	}

	void TicTacToeGameKMF::printBoard() {

		std::cout << std::endl;
		std::cout << " |1 2 3|" << std:: endl;
		for (int i = 0; i < 3; i++) {
			std::cout << " ------" << std::endl;
			std::cout << i + 1 << "|" << board[i][0] << "|" << board[i][1]
				<< "|" << board[i][2] << "|" << std::endl;
		}
	}

}

