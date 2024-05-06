#include <iostream>
#include <string>
#include "Casino.h"
#include "TicTacToeGame.h"
#include "S02469787.h"		// for TicTacToeAGP
#include "S02849570.h"		// for Hangman
#include "S02921882B.h"		// for Yahtzee
#include "S02902743.h"		// for BlackJack
#include "S02344566.h"		// for RockPaperScissorsGame
#include "S02424523A.h"		// for Baccarat
#include "S02591408.h"		// for Red_vs_Blue_TicTacToe
#include "S02239776.h"		// for TicTacToeGameKMF
#include "S01505380A.h"		// for WarCardGame
#include "S02392781.h"		// for Twenty48
#include "S02863875.h"		// for Roulette
#include "S02298183.h"		// for SquidGame

// class Casino implemetation file  XXX
namespace CSC2034 {
	void Casino::play(string gameName) {
		Casino* game = NULL;   //pointer should refer to object of subclass

		if (gameName == "TicTacToeGame")
			game = TicTacToeGame::makeGame(); // TicTacToeGame::makeGame();
		else if (gameName == "TicTacToeAGP")
			game = S02469787::TicTacToe::makeGame();
		else if (gameName == "Hangman")
			game = S02849570::Hangman::makeGame();
		else if (gameName == "Yahtzee")
			game = S02921882::Yahtzee::makeGame();
		else if (gameName == "BlackJack")
			game = S02902743::BlackjackGame::makeGame();
		else if (gameName == "RockPaperScissors")
			game = S02344566::RockPaperScissorsGame::makeGame();
		else if (gameName == "Baccarat")
			game = S02424523::Baccarat::makeGame();
		else if (gameName == "Red_vs_Blue_TicTacToe")
			game = S02591408::tttGameLogic::makeGame();
		else if (gameName == "TicTacToeGameKMF")
			game = S02239776::TicTacToeGameKMF::makeGame();
		else if (gameName == "WarCardGame")
			game = S01505380::WarCardGame::makeGame();
		else if (gameName == "Twenty48")
			game = S02392781::Twenty48::makeGame();
		else if (gameName == "Roulette")
			game = S02863875::Roulette::makeGame();
		else if (gameName == "SquidGame")
			game = S02298183::SquidGame::makeGame();
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
		out << "TitacToeAGP" << endl;
		out << "Hangman" << endl;
		out << "Yahtzee" << endl;
		out << "BlackJack" << endl;
		out << "RockPaperSciessors" << endl;
		out << "Baccarat" << endl;
		out << "Red_vs_Blue_TicTacToe" << endl;
		out << "TicTacToeGameKMF" << endl;
		out << "WarCardGame" << endl;
		out << "Twenty48" << endl;
		out << "SquidGame" << endl;
		return out;
	}
}
