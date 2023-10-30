#pragma once

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

enum cardType
{
	Highcard,
	OnePair,
	TwoPairs,
	ThreeOfaKind,
	Straight,
	Flush,
	FullHouse,
	FourOfaKind,
	StraightFlush
};
class PokerGame
{
	private:
		vector<int> playerCards;
		cardType Type;

	public:

		void Distribute(bool usedCards[52]);
		void set(vector<int> cards);
		void printCards();
		void sortCards();
		void evaluate();
		int getType();
		void compare(int type);


		bool isStraight();
		bool isFlush();
		bool isFourOfaKind();
		bool isFullHouse();
		bool isThreeOfaKind();
		bool isTwoPairs();
		bool isOnePair();
};

