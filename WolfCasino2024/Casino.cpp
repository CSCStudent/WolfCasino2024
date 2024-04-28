#include <iostream>
#include <string>
#include "Casino.h"
#include "TicTacToeGame.h"
#include "S02469787.h"

// class Casino implemetation file
namespace CSC2034 {
	void Casino::play(string gameName) {
		Casino* game = NULL;   //pointer should refer to object of subclass

		if (gameName == "TicTacToe")
			game = TicTacToeGame::makeGame(); // TicTacToeGame::makeGame();
		if (gameName == "TicTacToeAGP")
			game = S02469787::makeGame();
		else
			throw NoGame(gameName + " game not found!!");

		game->start();  // using late binding, invoke game start
		delete game;	// cleaning up heap

	}

	void Casino::start() {
		std::cout << "Subclass funtion start() is not defined." << endl;
	}

	Casino::~Casino() {
		std::cout << "Casino desctructor here" << endl;
	}

	ostream& operator << (ostream& out, NoGame& e) {
		out << endl;
		out << e.getMsg() << endl;
		out << "Here are your choices:" << endl;
		out << "TitactoeAGP" << endl;
		return out;
	}
}
