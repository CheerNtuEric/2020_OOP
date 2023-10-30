// Lab8.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<fstream>
using namespace std;
void Swap(int *A, int m, int n);
void Max_Heap_sort(int *A, int m);
void Max_heap_deletion(int *A, int str, int lm);
int key = 0;
int main() {
	//read file
	fstream file;
	file.open("input.txt");
	if (!file.is_open()) {
		cout << "Can't open the file!" << endl;
		return 0;
	}

	int Testcase = 0;
	int *A;
	file >> Testcase;
	A = new int[Testcase];
	int k = 0;
	for (int i = 0; i < Testcase; i++) {
		file >> k;
		A[i] = k;
	}
	for (int i = Testcase; i > -1; i--) {
		//while(key);
        Max_Heap_sort( A, i-1);
	}

    for(int i = Testcase-1 ; i>-1 ; i--){
		//while(key);
        Swap(A,0,i);
        Max_heap_deletion(A, 0, i-1);
    }
	 cout<< "Sorted List: ";
	for (int i = 0; i <Testcase; i++) {
		cout  << A[i] << " ";
	}
	cout << endl;

	return 0;
}
void Max_Heap_sort(int *A, int m) {
	int t = 0;
	key =1;
	if( m <= 0){
        key = 0;
        return;
	}
	if (m % 2 == 0){
		t = m / 2 - 1;
	}
	else if (m % 2 == 1){
		t = m / 2;
	}
	if (A[t] < A[m])
		Swap(A, t, m);
	Max_Heap_sort(A, t);
}

void Swap(int *A, int m, int n) {
	int temp = A[m];
	A[m] = A[n];
	A[n] = temp;
}
void Max_heap_deletion(int *A, int str, int lm){
    int larger;
    if((A[str+2] -A[str+1]) > 0 ) larger = 2;
	else larger = 1;

    if( (str+larger) > lm){
        return ;
	}
    if( (A[str] < A[str+larger]) ){
        Swap(A, str , str+larger);
        Max_heap_deletion(A, str+larger,lm);
    }
		else return;
        /*else if(A[str] < A[str+2]){
            Swap(A, str , str+2);
            Max_heap_deletion(A, str+2,lm-1)
        }*/
}
