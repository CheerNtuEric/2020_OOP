//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2020/05/01
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
	mNX = nx;
    mNZ = nz;
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //
	mNX = nx;
	mNZ = nz;
}
/*
specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys */
double MY_2048::computeScore()
{
	double score = 0;
	 for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int num = mBoard[ j ][ i ] ;
			//score += num;
			score += num*pow(num, 1.5);
		}
    }
	return score;
	
}
double best_score;
double MY_2048::perform_action_recursive(int level, unsigned char action)
{
	double score = 0.0;
	/*if(level == 0) {
		score = computeScore();
		if(score > best_score)
			best_score = score;
	}
	else{
		performAction(action);
		perform_action_recursive(level-1, action);
	}*/
	for(int i = 0 ; i<numSpecialKeys ; ++i){
		unsigned char action = specialKeys[ i ];
		performAction(action);
		
		//cout << score<<endl;
		if(level == 0) {
			//cout<<1<<endl;
			score = computeScore();

			return score;
		}
			
		else 
			perform_action_recursive( level-1, action );
	}
	

}
void MY_2048:: play_Auto()
{	
	int initBoard[MAX_2048_NZ][MAX_2048_NX];
	copy (mBoard, initBoard);
	double score[ 4 ];
	int level = 7;
	for(int i = 0 ; i<numSpecialKeys ; ++i){
		unsigned char action = specialKeys[ i ];
		score[i] = perform_action_recursive( level, action );
		//cout << score[i]<<endl;
	}
	int action_index = 0;
	best_score = score[0];
	for(int i=1 ; i <numSpecialKeys ; ++i){
		if(score[i] > best_score){
			best_score = score[i];
			action_index = i;
		}
	}
	copy ( initBoard, mBoard );
	if(best_score == score[0]) action_index = rand()%4;
	performAction( specialKeys[action_index]);//mBoard
	//performAction( specialKeys[1]);

}

void MY_2048::copy(const int src[][MAX_2048_NX], int tgt[][MAX_2048_NX]){
	 for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            tgt[ j ][ i ] = src[ j ][ i ];
        }
    }
}

void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[ j ][ i ] = ((MY_2048*)m)->mPreviousBoard[ j ][ i ];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    ///////////////////////////////////////
    //
    // Implement your own stuff
    //
	flg_AutoPlay = false;
	/*mNX = 0;
	mNZ = 0;*/
	for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[ j ][ i ] = 0;
			mPreviousBoard[ j ][ i ] = 0;
			mTmpBoard[ j ][ i ] = 0;
		}
    }
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
	cout << "MY_2048" << endl;
	cout << "Key usage:" << endl;
	cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
	cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
	cout << "3: generate randomly the numbers for all the cells" << endl;
	cout << "r: clear all the cells" << endl;
	cout << " " << endl;
	cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;

}

//
// randomly generate a new number 2 or 4
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
	bool zero = false;
	for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            if(mBoard[ j ][ i ] == 0){
				zero = true;
				break;
			}
		}
    }

	if (zero == false) return;
	int x = rand()%mNX, y = rand()%mNZ;
	while(mBoard[ x ][ y ] != 0){
		x = rand()%mNX, y = rand()%mNZ;
	}
	mBoard[ x ][ y ] = ( rand()%2 + 1 )*2;
	//mPreviousBoard[x][y] = 1;
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //    
	//actually up
	copy(mBoard,mPreviousBoard);
	for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int row = j+1;
			while ( row < mNZ && mBoard[row][i] == 0 ){
				row++;
			}
			if( (row < mNZ) && (mBoard[row][i] == mBoard[j][i])){
				mBoard[j][i] *= 2 ;
				mBoard[row][i] = 0;
			}
		}
    }

	for ( int i = 0; i < mNX; ++i ) {
		int count = 0; 
        for ( int j = 0; j < mNZ; ++j ) {
			if(mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[j][i];
			mBoard [j][i] = mBoard[count][i];
			mBoard[count][i] = temp;
			count++;
		}
    }


}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
	//coordinates are opposite.
	copy(mBoard,mPreviousBoard);
	//mPreviousBoard[1][1] = 2;
	for ( int i = 0; i < mNX; ++i ) {
        for ( int j = mNZ-1; j > -1; --j ) {
            int row = j-1;
			while ( row > -1 && mBoard[row][i] == 0 ){
				row--;
			}
			if( (row > -1)&& (mBoard[row][i] == mBoard[j][i]) ){
				mBoard[j][i] = 0 ;
				mBoard[row][i] *= 2;
			}
		}
    }

	for ( int i = 0; i < mNX; ++i ) {
		int count = 0; 
        for ( int j = mNZ-1; j >-1 ; --j ) {
			if(mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[j][i];
			mBoard [j][i] = mBoard[-count + mNZ - 1][i];
			mBoard[-count + mNZ - 1][i] = temp;
			count++;
		}
    }


}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
	copy(mBoard,mPreviousBoard);
	for ( int j = 0; j < mNX-1; ++j ) {
        for ( int i = 0; i < mNZ; ++i ) {
			int column = j+1;
			while ( (column < mNX) && (mBoard[i][column] == 0) ){
				column++;
			}
			if( (column!= mNX) && (mBoard[ i ][column] == mBoard[i][j])){
				mBoard[i][j] *= 2 ;
				mBoard[i][column] = 0;
			}

		}
    }

	for ( int j = 0; j < mNZ; ++j ) {
		int count = 0; 
        for ( int i = 0; i < mNX ; ++i ) {
			if( mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[j][i];
			mBoard [ j ][ i ] = mBoard[ j ][ count ];
			mBoard[ j ][ count ] = temp;
			count++;
		}
    }


}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
	copy(mBoard,mPreviousBoard);
	for ( int j = mNX - 1; j > 0; --j ) {
        for ( int i = 0; i < mNZ; ++i ) {
			int column = j-1;
			while ( column > -1 && mBoard[i][column] == 0 ){
				column--;
			}
			if( (column > -1) && (mBoard[ i ][column] == mBoard[i][j]) ){
				mBoard[i][j] *= 2 ;
				mBoard[i][column] = 0;
			}

		}
    }

	for ( int i = 0; i < mNZ ; ++i) {
		int count = 0; 
        for ( int j = mNX - 1 ; j > -1; --j ) {
			if( mBoard[i][j] == 0 )continue;
			int temp;
			temp = mBoard[i][j];
			mBoard [i][j] = mBoard[i][-count + mNX -1];
			mBoard[ i ][-count + mNX - 1] = temp;
			count++;
		}
    }

}
	

void MY_2048::generateNumbers_All_2to4( )
{
    //
    // Implement your own stuff
    //
	for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
			int index, num;
			index = rand() % 2;
			if(index == 1) num = 2;
			else if(index == 0) num = 4;
            mBoard[ j ][ i ] = num;
		}
    }
}
void MY_2048::generateNumbers_All_2to8( )
{
    //
    // Implement your own stuff
    //
	for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
			int index, num;
			index = rand() % 3;
			if(index == 1) num = 2;
			else if(index == 0) num = 4;
			else if (index == 2) num = 8;
            mBoard[ j ][ i ] = num;
		}
    }
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
	for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
			int index, num;
			index = rand() % 11;
			num = 2<<(index ); // index = 10 , num =2048
            mBoard[ j ][ i ] = num;
		}
    }
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;

    case 'a':
    case 'A':
        flg_AutoPlay = true;
		play_Auto();
		flg_AutoPlay = false;
        break;
    }
}

void MY_2048::performAction( unsigned char key ) {
bool flgDone = false;

    switch( key ) {
		case GLUT_KEY_UP:
			flgDone = true;
			moveUp( );
			mEvent = GLUT_KEY_UP;
			break;
		case GLUT_KEY_DOWN:
			flgDone = true;
			moveDown( );
			mEvent = GLUT_KEY_DOWN;

			break;
		case GLUT_KEY_LEFT:
			flgDone = true;
			moveLeft( );
			mEvent = GLUT_KEY_LEFT;

			break;
		case GLUT_KEY_RIGHT:
			flgDone = true;
			moveRight( );
			mEvent = GLUT_KEY_RIGHT;

			break;
    }
    if ( flgDone ) {
        generateNumber( );
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

double MY_2048::play_Smart(
	int numForwardMoves,
	unsigned char action_index
	)
{
	double score = 0.0;

	int initBoard[MAX_2048_NZ][MAX_2048_NX];
	copy (mBoard, initBoard);
	double fScore = play_Smart_Recursive(
		numForwardMoves, action_index, initBoard);
	copy(initBoard, mBoard);
	score = fScore;
	return score;
}

double MY_2048::play_Smart_Recursive(
	int numSteps, unsigned char action_key, 
	int board[][MAX_2048_NX]
)
{
	double tScore = 0.0;
	if (numSteps <= 0){
		tScore = computeScore();
		return tScore;
	}

	copy(board, mBoard);
	handleSpecialKeyPressedEvent( action_key );
	int initBoard[MAX_2048_NZ][MAX_2048_NX];
	copy( mBoard, initBoard);
	double rate = 0.85;
	double score = 0.0;

	for(int i =0; i<numSpecialKeys;++i){
		score = 
			score*pow(rate, numSteps)
			+
			play_Smart_Recursive(
			numSteps - 1, specialKeys[ i],
			initBoard );
	}
}
double MY_2048::computeScore() const
{
	double score = 0.0;
	pair<int,int> largest;
	double largest_score = 0.0;
	for(int j =0; j <mNZ; ++j){
		for(int i = 0; i<mNX; i++){
			double s = mBoard[ j ][ i];
			if(s > largest_score){
				largest_score = s;
				largest.first = j;
				largest.second = i;
			}
			score += s*pow(s, 0.35);
		}
	}
}
//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//
void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
}
