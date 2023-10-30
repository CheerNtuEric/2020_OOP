#include <iostream>
#include <stdlib.h>
#include "PokerGame.h"
#include <time.h>
#include <algorithm>
using namespace std;

void cheatInput(vector<int> &player)
{
	//TO_DO: Ask user input five number and store them to vector of player
	for (int i = 0, j = 0 ; i < 5 ; i++) {
		cin >> j;
		player.push_back(j);
	}   
}

int main()
{
	bool Exit = false;

	while (!Exit)
	{
		PokerGame player1 , player2;
		//player1.playerCards.clear();
		//player2.playerCards.clear();
		vector<int> cheatCards1, cheatCards2;
		bool usedCards[52] = { false };
		char GameType;
		cout << "Enter S to start the game, C to enter cheating mode, Q to Exit the process" << endl;
		cin >> GameType;

		switch (GameType)
		{
			case 's':
			case 'S':
				//Normal mode, generate five cards for each players
				player1.Distribute(usedCards);
				player2.Distribute(usedCards);

				//Evaluate the type of cards
				player1.evaluate();
				player2.evaluate();

				//Print the cards of each players
				player1.printCards();
				player2.printCards();

				//Compare and output winner
				player1.compare(player2.getType());
				break;
			case 'c':
			case 'C':
				//Cheat mode , input the player cards
				cout << "Input player1's cards:";
				cheatInput(cheatCards1);
				cout << "Input player2's cards:";
				cheatInput(cheatCards2);
				player1.set(cheatCards1);
				player2.set(cheatCards2);

				//Evaluate the type of cards
				player1.evaluate();
				player2.evaluate();

				//Print the cards of each players
				cout << "Player cards:" <<endl;
				player1.printCards();
				cout << "Player cards:" <<endl;
				player2.printCards();

				//Compare and output winner
				player1.compare(player2.getType());
				break;
			case 'q':
			case 'Q':
				Exit = true;
				break;
			default:
				break;
		}
		cout << endl;
	}
}
