#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iterator>
using namespace std;

class PrimeFactorization {
private:
	int num1, num2;
	vector<int> num1_factor, num2_factor;

public:
	PrimeFactorization() {
		//TO_DO: initial constructor
	}
	PrimeFactorization(int _a, int _b) {
		//TO_DO: _a means the first integer and _b means the second integer
        num1 = _a;
        num2 = _b;
	}
	void Get_Prime_Factorization() {
		//TO_DO: Prime factorization num1 and num2, push result to the num1_factor and num2_factor.
        for(int i = 2; i <= num1 ; i++){
            while (num1 % i == 0 ){
                num1 /= i;
                num1_factor.push_back(i);
            }
        }
        for(int i = 2; i <= num2 ; i++){
            while (num2 % i == 0 ){
                num2 /= i;
                num2_factor.push_back(i);
            }
        }
	}

	void Print_Prime_Factorization() {
		//TO_DO: Print num1_factor and num2_factor.
        cout << "num1_Prime_factor : \"";
        for(int i = 0 ; i < num1_factor.size() ; i++){
            cout << num1_factor[i] << " ";
        }
        cout << "\"" << endl;
        cout << "num2_Prime_factor : \"";
        for( int i = 0 ; i < num2_factor.size() ; i++){
            cout << num2_factor[i] << " ";
        }
        cout << "\"" << endl;
	}

	void Print_GCD_Factorization() {
		//TO_DO: Use num1_factor and num2_factor to find prime factorization of GCD and print the result.

		//copy(num1_factor.begin(), num1_factor.end()-1, temp1);
		//copy(num2_factor.begin(), num2_factor.end()-1, temp2);

		cout<< "GCD_Prime_Factor : \"";
		int k = 0;
		for(int i = 0 ; i < num1_factor.size() ; i++)
            for( int j = 0 ; j< num2_factor.size() ; j++ )
                if(num1_factor[i] - num2_factor[j] == 0 ){
                    cout << num1_factor[i]<<" ";
                    num2_factor[j] = 0;
                    k++;
                    break;
                }
        if (k == 0) cout << "1";
		cout << "\"\n" ;
		num1_factor.clear();
		num2_factor.clear();
	}
};

int main() {
	int n;
    fstream file;
    file.open("input.txt", ios::in);
	/* Do something to read the input.txt file*/
    if(!file){
        cerr << "Can't open the file!\n";
        exit(1);
    }
    file >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
        file >> a >> b;

		/*Read a and b from input.txt file*/

		cout << "num1 = " << a << endl;
		cout << "num2 = " << b << endl;

		PrimeFactorization PF(a, b);

		PF.Get_Prime_Factorization();
		PF.Print_Prime_Factorization();
		PF.Print_GCD_Factorization();

		cout << endl;

	}

	system("PAUSE");
	return 0;
}
