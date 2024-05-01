#include <iostream>
#include <string>
#include "Casino.h"
#include "TicTacToeGame.h"
#include "S02469787.h"
#include "S02849570.h"
#include "S02921882B.h"

// class Casino implemetation file  XXX
namespace CSC2034 {
	void Casino::play(string gameName) {
		Casino* game = NULL;   //pointer should refer to object of subclass

		if (gameName == "TicTacToeGame")
			game = TicTacToeGame::makeGame(); // TicTacToeGame::makeGame();
		if (gameName == "TicTacToeAGP")
			game = S02469787::makeGame();
		if (gameName == "Hangman")
			game = S02849570::Hangman::makeGame();
		if (gameName == "Yahtzee")
			game = S02921882::Yahtzee::makeGame();
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
		out << "Hangman" << endl;
		out << "Yahtzee" << endl;
		return out;
	}
}
