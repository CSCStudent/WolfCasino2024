// in solution
/**
 * Program Name: Baccarat Casino Game
 * Description: This program allows the user to play a simplified game of Baccarat against the computer.
 *				The rules are the same as traditional Baccarat, However, the user may only make one bet per hand.
 *              The game is also single player at the moment.
 * Author: Brandon Sanders
 * Date Created: 4/29/2024
 * Version: 1.0
 * Contact Information: Brandman303@gmail.com
 */
#include "S02424523D.h"
#include "S02424523C.h"
#include "S02424523B.h"
#include "S02424523A.h"
#include <iostream>
#include <thread>
#include <chrono>
/*
* ToDo: 
* -program file size is continually growingw with each play. Fix!!!!
* -files are being used from two different directories. Make sure to submit correct files.!!!!
* -create formatted card output
* -maybe add messages for what happens during hand. for example: if player and banker stands on 6 and 7 let the user know.
* -natural stands output to the console twice. Elminate this.
* -
*/
using namespace std;
namespace S02424523 {
	//function prototypes
	void playHand(Deck& deck, Hand& player, Hand& banker);
	void initialDeal(Deck& deck, Hand& player, Hand& banker);
	void deal(Deck& deck, Hand& hand);
	void printHands(Hand& player, Hand& banker);
	int tableResult(Hand player, Hand banker);
	long betResult(long& wallet, int betType, long bet, int winner);
	long makeBet(long& wallet);
	void welcomeMessage();
	Baccarat::Baccarat() {

	}

	Baccarat* Baccarat::makeGame() {
		return new Baccarat;
	}

	void Baccarat::start() {
		Deck deck;
		Hand player;
		Hand banker;
		//long wallet = 1000;

		deck.shuffle();
		welcomeMessage();
		playHand(deck, player, banker);
		cout << "Game Over" << endl;
	}
	void Baccarat::playHand(Deck& deck, Hand& player, Hand& banker) {
		bool play = true;
		long wallet = 1000;
		long bet = 5;
		long result = 0;
		
		do {
			if (deck.getSize() < 10) {
				deck.reset();
				cout << "Deck is being reshuffled" << endl;
			}
			int winningHand = 0;
			string yesNo;
			int betType;
			bool natural = false;
			cout << "Wallet: $" << wallet << endl;
			cout << "1. Bet on player" << endl;
			cout << "2. Bet on banker" << endl;
			cout << "3. Bet on Tie" << endl;
			cout << "Please enter your choice by corresponding number: " << endl;
			cin >> betType;

			switch (betType) {
			case 1:
				cout << "You have chosen to bet on the Player, with payout 1:1" << endl;
				break;
			case 2:
				cout << "You have chosen to bet on the Banker, with payout 0.95:1" << endl;
				break;
			case 3:
				cout << "You have chosen to bet on  a Tie, with payout 8:1" << endl;
				break;
			}
			bet = makeBet(wallet);
			initialDeal(deck, player, banker);
			cout << "Player's hand: " << player.toString(player) << endl;
			cout << "Banker's hand: " << banker.toString(banker) << endl;
			if (player.handTotal() == 8 || player.handTotal() == 9 || banker.handTotal() == 8 || banker.handTotal() == 9) {
				natural = true;
			}
			if (!natural) {
				if (player.handTotal() == 6 || player.handTotal() == 7) {
					if (banker.handTotal() <= 6) {
						deal(deck, banker);
					}
				}
				if (player.handTotal() <= 5) {
					deal(deck, player);
					switch (banker.handTotal()) {
					case 1:
						deal(deck, banker);
						break;
					case 2:
						deal(deck, banker);
						break;
					case 3:
						if (player.getCard(2).getRank() != 8) {
							deal(deck, banker);
						}
						break;
					case 4:
						if (player.getCard(2).getRank() < 8 && player.getCard(2).getRank() > 1) {
							deal(deck, banker);
						}
						break;
					case 5:
						if (player.getCard(2).getRank() < 8 && player.getCard(2).getRank() > 3) {
							deal(deck, banker);
						}
						break;
					case 6:
						if (player.getCard(2).getRank() < 8 && player.getCard(2).getRank() > 5) {
							deal(deck, banker);
						}
						break;
					default:
						break;
					}
				}
				cout << endl << "DEALING" << endl;
				for (int i = 0; i < 3; i++) {
					cout << "." << endl << flush;
					this_thread::sleep_for(chrono::seconds(1));
				}
				cout << endl;
			}
			printHands(player, banker);
			winningHand = tableResult(player, banker);

			if (winningHand > 0) {
				cout << "Player Hand wins!" << endl;

			}
			if (winningHand < 0) {
				cout << "Banker Hand wins!" << endl;
			}
			if (winningHand == 0) {
				cout << "Hands Tie!" << endl;
			}
			betResult(wallet, betType, bet, winningHand);
			cout << "wallet: $" << wallet << endl; 
			if (wallet < 5) {
				cout << "You're out of money!"
					<< endl << "Too bad, you were one win streak away from winning it big..." << endl;
				break;
			}
			cout << "Play Again? (Y/N)" << endl;
			std::cin >> yesNo;
			(yesNo == "Y" || yesNo == "y") ? play = true : play = false;
			player.clearHand();
			banker.clearHand();

		} while (play);
	}
	//Initial deal of two cards to each player
	void Baccarat::initialDeal(Deck& deck, Hand& player, Hand& banker) {
		if (player.handSize() == 0 && banker.handSize() == 0) {
			while (banker.handSize() < 2) {
				player.addToHand(deck.getCard());
				banker.addToHand(deck.getCard());
			}
		}
	}
	//deals a single card
	void Baccarat::deal(Deck& deck, Hand& hand) {
		if (hand.handSize() < 3) {
			hand.addToHand(deck.getCard());
		}
	}
	//prints the player and banker hands.
	void Baccarat::printHands(Hand& player, Hand& banker) {
		cout << "player's Hand: " << player.toString(player) << endl;
		cout << "Banker's Hand: " << banker.toString(banker) << endl;
	}
	//handles the winnings or losses. may not need the wallet, just change it in play function.
	long Baccarat::betResult(long& wallet, int betType, long bet, int winner) {
		long result = 0; 
		switch (betType) {
		case 1:
			if (winner != 0) {
				if (winner > 0) {
					result = (bet * 2);
					wallet += result;
				}
			
			}
			else {
				wallet += bet;
			}
			break;
		case 2:
			if (winner != 0) {
				if (winner < 0) {
					result = bet * 1.95;
					wallet += result;
				}
			}
			else {
				wallet += bet;
			}
			break;
		case 3:
			if (winner == 0) {
				result = bet * 9;
				wallet += result;
			}
			break;
		default:
			cout << "something went wrong in bet result." << endl;
			break;
		}
		if (result != 0) {
			cout << "Bet result: +$" << result << endl;
		}
		else {
			if (winner != 0) {
				cout << "Bet result: -$" << bet << endl;
			}
			else {
				cout << "Bet result: push" << endl;
			}
		}
		return result;
	}

	long Baccarat::makeBet(long& wallet) {
		long bet = 5;
		bool invalidBet = true;
		do {
			cout << "Minimum bet is $5. Place your bets: " << endl;
			cin >> bet;
			if (bet > wallet) {
				cout << "Bet exceeds wallet. Please, re-enter yout bet." << endl;
			}
			else if (bet < 5) {
				cout << "Bet is below the minimum. Please, re-enter your bet." << endl;
			}
			else {
				invalidBet = false;
				wallet -= bet;
			}
		} while (invalidBet);
		return bet; //check if it returns correct value.
	}
	//consider renaming to tableResult or determineWinner
	int Baccarat::tableResult(Hand player, Hand banker) {
		if (player.handTotal() > banker.handTotal()) {
			return 1;
		}
		if (player.handTotal() < banker.handTotal()) {
			return -1;
		}
		return 0;
	}
	void welcomeMessage() {
		cout << endl << "Welcome to Baccarat!" << endl;
		cout << endl << "How To Play: " << endl;
		cout << "The goal of baccarat is to get as close to 9 as possible with a maximum hand of 3 cards" << endl;
		cout << "First you will bet on the Banker's hand (the dealer), Player's hand (you), or a tie." << endl;
		cout << "You win if the hand you bet on wins the table." << endl;
		cout << endl << "Rules: " << endl;
		cout << "Banker payout is 0.95:1" << endl << "Player payout is 1:1" << endl << "Tie payout is 8:1" << endl
			<< "Starting cash is $1000" << endl << "Minimum Bet is $5 and bets may not exceed wallet size" << endl << endl;
	}
}