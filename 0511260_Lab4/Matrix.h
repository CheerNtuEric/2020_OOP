#ifndef _Matrix_
#define _Matrix_

#include<iostream>
#include<vector>

using namespace std;

class matrix
{
public:
	vector< vector<int> > M;

	matrix();
	matrix(int m, int n);
	matrix(vector<vector<int> > &m);


	matrix Mul(matrix m1);
	void Inverse();
	void Inv(int n, vector<vector<int> > &m);
	bool SquareMatrix();
	void GetDet();
	int Det(int n, vector<vector<int> > &m);
	void Print();
};


#endif // !_Matrix_

