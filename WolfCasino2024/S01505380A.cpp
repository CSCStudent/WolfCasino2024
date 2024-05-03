#include "S01505380A.h"

using namespace std;

namespace S01505380
{
		
	void WarCardGame::start() {
		deck masterDeck;
		deck deck1;
		deck deck2;
		deck middlePile;


		masterDeck.shuffle();

		while (!masterDeck.isEmpty()) {
			deck1.addCard(masterDeck.drawCard());
			deck2.addCard(masterDeck.drawCard());

		}

		while (!deck1.isEmpty() && !deck2.isEmpty()) {
			thisIsWar(deck1, deck2, middlePile);

		}

	}
	WarCardGame* WarCardGame::makeGame() {
		return new WarCardGame;
	}



  void WarCardGame::thisIsWar(deck& deck1, deck& deck2, deck& middlePile) {

		system("pause");

		card card1(5, 13);
		card card2(5, 13);

		card1 = deck1.drawCard();
		card2 = deck2.drawCard();

		middlePile.addCard(card1);
		middlePile.addCard(card2);


		cout << card1 << endl;
		cout << card2 << endl;


		if (card1 < card2) {
			deck2.addToDeck(middlePile);
			cout << "Player 2 takes the pile" << endl;
			cout << "Player 1's deck is " << deck1.deckSize() << " cards" << endl;
			cout << "Player 2's deck is " << deck2.deckSize() << " cards" << endl;

			if (deck1.deckSize() == 52) {
				cout << "Game Over, Player 2 Wins!" << endl;
			}
			if (deck2.deckSize() == 52) {
				cout << "Game Over, Player 1 Wins!" << endl;
			}

		}
		if (card1 > card2) {
			deck1.addToDeck(middlePile);
			cout << "Player 1 takes the pile" << endl;
			cout << "Player 1's deck is " << deck1.deckSize() << "cards" << endl;
			cout << "Player 2's deck is " << deck2.deckSize() << " cards" << endl;

			if (deck1.deckSize() == 52) {
				cout << "Game Over, Player 2 Wins!" << endl;
			}
			if (deck2.deckSize() == 52) {
				cout << "Game Over, Player 1 Wins!" << endl;
			}
		}
		if (card1 == card2) {
			cout << "WAR BEGINS: " << endl;
			middlePile.addCard(deck1.drawCard());
			middlePile.addCard(deck1.drawCard());
			middlePile.addCard(deck1.drawCard());

			middlePile.addCard(deck2.drawCard());
			middlePile.addCard(deck2.drawCard());
			middlePile.addCard(deck2.drawCard());

			thisIsWar(deck1, deck2, middlePile);
		}
	}

}//end of namespace csc2034
