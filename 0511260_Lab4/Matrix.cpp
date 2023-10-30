#include "Matrix.h"
#include  <math.h>
matrix::matrix()
{
//	M = { {} };
}

matrix::matrix(int m, int n)
{
	//TO_DO: Use std::cin to initialize a matrix of size m * n

    for(int i =0 ; i < m ; i++){
		vector<int> temp;
        for(int j = 0, k = 0 ; j < n ; j++ ){
          std :: cin >> k;
		   temp.push_back(k);
		}
		M.push_back(temp);
	}
}

matrix::matrix(vector< vector<int > >& m)
{
	M = m;
}

matrix matrix::Mul(matrix m1)
{

	if (M[0].size() != m1.M.size()) //m1 column¡Am2 row
	{
		cout << "Cannot do multiplication!" << endl;
		return matrix();
	}
	else
	{
		//TO_DO: Multiply two matrices and print the result.
		vector< vector< int > > Multi;

		for(int i = 0 ; i < M.size() ; i++){
            vector<int> temp;
			int sum = 0;
			for(int N = 0 ; N< m1.M[0].size() ; N++){
				for(int k = 0, j = 0; k < M[0].size(), j < m1.M.size() ; k++, j++){

                     sum += M[i][k]* m1.M[j][N];
				}	
				temp.push_back(sum);
				sum = 0;
			}
			Multi.push_back(temp);
		}
		return matrix(Multi);
	}
	
}
void matrix::Inv(int n ,vector< vector< int > >& m)
{		
		vector<vector< int >> send_back ;

            for( int c = 0 ; c < n ; c++){
				vector<int> temp_send_back;
                for( int l = 0 ; l < n; l++){
					vector< vector<int > > temp_inv;
                    for( int i = 0; i < n; i++)
                    {   
						vector<int> submat;
                        if(i == l)continue;
						for(int j = 0; j < n; j++)
						{
                            if (j == c)continue;
							submat.push_back( m[i][j] );
                        }
						temp_inv.push_back(submat);
                    }
					temp_send_back.push_back(pow ((double)-1, (double)(c+l) ) * Det(n-1,temp_inv));
                }
				send_back.push_back(temp_send_back);
			}
				m = send_back;
			
}
void matrix::Inverse()
{
    int n = M.size(),d ;
	//TO_DO: If inverse matrix exist, find and print inverse matrix.
	 
	if (!SquareMatrix() )
		cout << "The Inverse Not Exist." << endl;
	else if(Det(n,M) == 0)
		cout << "The Inverse Not Exist." << endl;
	else if(n > 2){
		d = Det(n,M);
		cout << "Inverse matrix : " << endl;
		cout << "1/" << d << "*\n";
        Inv(n,M);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << M[i][j] << " ";
            }
            cout<<endl;
        }
    }
	else{
		cout<<M[1][1]<<" "<<-M[0][1]<<endl;
		cout<<-M[1][0]<<" "<<M[0][0]<<endl;
	}
}
bool matrix::SquareMatrix()
{

	//TO_DO: Return true if matrix is a square matrix, otherwise return fasle.

	if(M.size() != M[0].size())
        return false;
    else
        return true;
}

void matrix::GetDet()
{
    int n = M.size();
	if (!SquareMatrix())
		cout << "Not a Square Matrix" << endl;
	else
		cout << "Determinant of matrix : " << Det(n,M) << endl;

}

int matrix::Det(int n ,vector< vector< int > >& m)
{

	//TO_DO: Compute the determinant of matrix m.
		int d = 0;
        if (n == 2)
        {	
			//cout << m[0][0] <<" "<<m[0][1]<<" "<<m[1][0]<<" "<<m[1][1]<<endl;
            return (m[0][0] * m[1][1]) - (m[1][0] * m[0][1]);
        }
        else
        {
            for(int c = 0; c < n; c++){
				
				vector<vector<int>> submat;
                for(int i = 1; i < n; i++)
                {
					vector<int> temp_submat;
                    for(int j = 0; j < n; j++)
                    {
                        if (j == c)
                        {
                            continue;
                        }
					//cout << m[i][j] << " ";
                       temp_submat.push_back(m[i][j]);
                    }
					submat.push_back(temp_submat);
                }
			//cout << submat[0][0] <<" "<<submat[0][1]<<" "<<submat[1][0]<<" "<<submat[1][1]<<endl;
            d +=  pow((double)-1 ,c) * m[0][c]* Det(n - 1 ,submat);
            //cout <<pow((double)-1 ,c)<<" "<<m[0][c]<<" "<<d<< endl;
			} 
		
		return d;
        } 
}

void matrix::Print()
{
	for (int i = 0; i < M.size(); i++) {
		for (int j = 0; j < M[0].size(); j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}
