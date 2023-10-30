#include "PokerGame.h"
#include <algorithm>
#include <time.h>
void PokerGame::Distribute(bool usedCards[])
{
	//TO_DO: Random generate five cards to player
	//Hint: Use usedCards to record which card have been distributed
	playerCards.clear();
	srand((unsigned)time(NULL));
	for(int i = 0, j ; i < 5 ;){
		j = rand() % 52;
		if(!usedCards[j]){
			playerCards.push_back(j);
            usedCards[j] = true;
            i++;
		}
		//else playerCards.erase(playerCards.begin());
		//cout << i << " "<< j<< endl;
	}
}//shuffle

void PokerGame::set(vector<int> cards)
{
	//TO_DO: Set the cards to player
        playerCards = cards;
}

void PokerGame::printCards()
{
	//cout << "Player cards:";
	int c, d;
	for (int i = 0; i < 5; i++)
	{
		//TO_DO: Print the player's cards.
		// For example: "C1" "S2" "H3" ...
        c = playerCards[i] / 13;
		d = playerCards[i] % 13;
        switch(c){
            case 0:
				cout << "C" << d + 1<<" ";
				break;
            case 1:
				cout << "D" << d + 1 <<" ";
				break;
            case 2:
                cout << "H" << d + 1<<" ";
				break;
            case 3:
                cout << "S" << d + 1<<" ";
				break;
		}
	}
	cout << endl;
}

void PokerGame::sortCards()
{   //TO_DO: Sort the cards accroding to thier number
    int temp;
    for( int i = 0 ; i < 5 ; i++)
        for( int k = 0 ; k < 5-i ; k++)
            if( playerCards[i] % 13 > playerCards[i+k] % 13 ){
                temp = playerCards[i];
                playerCards[i] = playerCards[i+k];
                playerCards[i+k] = temp;
            }
	//sort(playerCards.begin(), playerCards.end());
}

void PokerGame::evaluate()
{
	sortCards();
	if (this->isStraight() && this->isFlush())
	{
		Type = StraightFlush;
	}
	else if (this->isFourOfaKind())
	{
		Type = FourOfaKind;
	}
	else if (this->isFullHouse())
	{
		Type = FullHouse;
	}
	else if (this->isFlush())
	{
		Type = Flush;
	}
	else if (this->isStraight())
	{
		Type = Straight;
	}
	else if (this->isThreeOfaKind())
	{
		Type = ThreeOfaKind;
	}
	else if (this->isTwoPairs())
	{
		Type = TwoPairs;
	}
	else if (this->isOnePair())
	{
		Type = OnePair;
	}
	else
	{
		Type = Highcard;
	}
}

int PokerGame::getType()
{
	return Type;
}

void PokerGame::compare(int type)
{
	//TO_DO: Compare the type and output who is winner
    if (Type - type >0)
        cout << "Player1 win !";
    else if (Type - type < 0)
        cout << "Player2 win !";
    else cout << "Draw.";
}

bool PokerGame::isStraight()
{
	//TO_DO: Check whether the hand of cards is Straight or not
	for(int i = 0 ; i < 4 ;){
        if( (playerCards[i+1]%13 - playerCards[i]%13) == 1)
            i++;
        else
            return false;
	}
	return true;
}

bool PokerGame::isFlush()
{
	//TO_DO: Check whether the hand of cards is Flush or not
	for(int i = 0 ; i < 4 ;){
        if( (playerCards[i+1]/13 - playerCards[i]/13) == 0)
            i++;
        else
            return false;
	}
	return true;
}

bool PokerGame::isFourOfaKind()
{
	//TO_DO: Check whether the hand of cards is FourOfaKind or not
	if(playerCards[0]%13 - playerCards[1] % 13 < 0){
        for(int i = 1 ; i <=3 ;){
            if(playerCards[i+1]%13 - playerCards[i]%13 == 0)
            i++;
            else break;
            if (i == 4) return true;
        }
	}
	if(playerCards[0]%13 - playerCards[1] % 13 == 0){
        for(int i = 0 ; i <=2 ;){
            if(playerCards[i+1]%13 - playerCards[i]%13 == 0)
            i++;
            else break;
            if (i == 3) return true;
        }
	}
	return false;
}

bool PokerGame::isFullHouse()
{
	//TO_DO: Check whether the hand of cards is FullHouse or not
	if(PokerGame::isThreeOfaKind() && PokerGame::isOnePair())
        return true;

	return false;
}
bool check_three(int x, int y, int z)
{
    if(x == y || x == z || y ==z)
        return true;
    else
        return false;
}
bool PokerGame::isThreeOfaKind()
{
	//TO_DO: Check whether the hand of cards is ThreeOfaKind or not
	for(int i = 4 ; i >= 3;){
        if ( playerCards[i] - playerCards[i-1] == 0 )
            i--;
        else break;
        if ( i == 2) return true;
	}
	for(int i = 0 ; i <=1;){
        if  (playerCards[i] - playerCards[i+1] == 0)
            i++;
        else break;
        if ( i == 2) return true;
	}
	return false;
}

bool PokerGame::isTwoPairs()
{
	//TO_DO: Check whether the hand of cards is TwoPairs or not
	int a, b, c, d, e;
	a = playerCards[0]%13;
	b = playerCards[1]%13;
	c = playerCards[2]%13;
	d = playerCards[3]%13;
	e = playerCards[4]%13;
	if ( (a==b) && (check_three(c,d,e) ==1 ) ){
			return true;
		}
		else if( (a==c) && (check_three(b,d,e) ==1 ) ){
			return true;
		}
		else if( (a==d) && (check_three(c,b,e) ==1 ) ){
			return true;
		}
		else if( (a==e) && (check_three(b,c,d) ==1 ) ){
			return true;
		}
		else if( (b==c) && (check_three(a,d,e) ==1 ) ){
			return true;
		}
		else if( (b==d) && (check_three(a,c,e) ==1 ) ){
			return true;
		}
		else if( (b==e) && (check_three(a,c,d) ==1 ) ){
			return true;
		}
		else if( (c==d) && (check_three(a,b,e) ==1 ) ){
			return true;
		}
		else if( (c==e) && (check_three(a,b,d) ==1 ) ){
			return true;
		}
		else if( (d==e) && (check_three(a,b,c) ==1 ) ){
			return true;
		}
		else{
			return false;
		}
}

bool PokerGame::isOnePair()
{
    //TO_DO: Check whether the hand of cards is OnePair or not
    int a, b, c, d, e;
    a = playerCards[0]%13;
	b = playerCards[1]%13;
	c = playerCards[2]%13;
	d = playerCards[3]%13;
	e = playerCards[4]%13;
	if ( a==b || a==c || a==d || a==e || b==c || b==d || b==e || c==d || c==e || d==e){
        return true;
    }
	else return false;
}



