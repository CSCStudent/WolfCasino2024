#include <vector>
#include "S02977128A.h"

using namespace std;

namespace S02977128 {
	
	void GoFish::start() {
		Deck deck;
		deck.shuffle();
		Player p1;
		Player p2;
		vector<Player> players;
		players.push_back(p1);
		players.push_back(p2);
//		deal(vector<Player>&, Deck);
		int playerNumber = 0;

		while ((players[0].getPoints() < 7 && players[1].getPoints() < 7) && !deck.getCards().empty()) {
			if (!play(players, playerNumber, deck)) {
				playerNumber++;
				system("CLS");
			}
			for (Player p : players) {
				if (p.getHand().empty() && !deck.getCards().empty())
					p.take(deck.draw());
			}
			std::this_thread::sleep_for(std::chrono::seconds(2));

		}

		system("CLS");
		if (players[0].getPoints() > players[1].getPoints())
			cout << "Player 1 wins " << players[0].getPoints() << " to " << players[1].getPoints() << "!";
		else if (players[1].getPoints() > players[0].getPoints())
			cout << "Player 2 wins " << players[1].getPoints() << " to " << players[0].getPoints() << "!";
		else
			cout << "Tie game! Both players finished with " << players[0].getPoints() << " points!";
	}

	GoFish* GoFish::makeGame() {
		return new GoFish;
	}

	void GoFish::deal(vector<Player>& players, Deck& deck) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < players.size(); j++) {
				players[j].deal(deck.draw());
			}
		}
	}

	bool GoFish::play(vector<Player>& players, int& turn, Deck& deck) {
		//setup
		turn = turn % 2;
		int notTurn = 0;
		if (turn == 0) {
			notTurn = 1;
		}
		int displayTurn = 2;
		if (turn == 0) {
			displayTurn = 1;
		}
		players[turn].sortHand();
		cout << players[turn].showHand() << endl;

		int pick;
		printf("Player %d, pick a card from your hand. Valid numbers range from 1 - 13 (Ace = 1, Jack = 11, Queen = 12, King = 13): ", displayTurn);
		cin >> pick;
		pick--;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		while ((pick > 12 || pick < 0) || !players[turn].inHand(pick)) {
			printf("Player %d, pick a card from your hand. Valid numbers range from 1 - 13 (Ace = 1, Jack = 11, Queen = 12, King = 13): ", displayTurn);
			cin >> pick;
			pick--;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		vector<int> indices;
		// Done backwards so the indices of correctly guessed cards stay the same
		for (int i = (int)players[notTurn].getHand().size(); i > 0; i--) {
			if (players[notTurn].getHand()[i - 1].getRank() == pick) {
				indices.push_back(i - 1);
			}
		}
		bool flag;
		// do we go fish?
		if (!indices.empty()) {
			for (int i : indices) {
				players[turn].take(players[notTurn].give(i));
			}
			cout << "Player " << displayTurn << " guessed correctly! Go again!" << "\n\n";
			flag = 1;
		}
		else {
			cout << "  ____          __ _      _     _ \n"
				"/ ___ | ___    / _(_)___ | |__ | |\n"
				"| |  _ / _ \\  | |_| / __ | '_ \\| |\n"
				"| |_| | (_) | |  _| \\__ \\| | | |_|\n"
				"\\____ |\\___/  |_| |_|___/_ | |_(_)";
			std::this_thread::sleep_for(std::chrono::seconds(4));
			players[turn].deal(deck.draw());
			flag = 0;
		}
		pointsCheck(players);
		return flag;
	}

	void GoFish::pointsCheck(vector<Player>& players) {
		for (Player& p : players) {
			for (Card c : p.getHand())
				p.haveSuit(c.getRank());
		}
	}

}