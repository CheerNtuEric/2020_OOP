// Lab8.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<fstream>
using namespace std;
void Swap(int *A, int m, int n);
void Max_Heap_sort(int *A,int *B, int n);
void Max_heap_deletion(int *A, int str, int lm);
void insert_max_heap(int *A, int i);

//int key = 0;
int main() {
	//read file
	fstream file;
	file.open("input.txt");
	if (!file.is_open()) {
		cout << "Can't open the file!" << endl;
		return 0;
	}

	int n = 0;
	int *A, *B;
	file >> n;
	A = new int[n+1];
	B = new int[n+1];
	int k = 0;
	for (int i = 1; i <= n; i++) {
		file >> k;
		//cout << k << " ";
		A[i] = k;
		if (i>1) insert_max_heap(A,i);
	}

	//cout << endl;
/*
	for (int i = 1; i <= n; ++i) {
        cout << A[i] << " ";
    }

    cout << endl;
*/

    Max_Heap_sort(A, B, n);

    for (int i = 0; i < n; ++i) {
        cout << B[i] << " ";
    }
    cout << endl;

	return 0;
}

void insert_max_heap(int *A, int i)
{

    int p = i/2;
    if (p<=0) return;
    if (A[p] < A[i]) {
        swap(A[p], A[i]);
        insert_max_heap(A,p);
    }
}


void Max_Heap_sort(int *A, int *B, int n) {

    void max_heap_delete(int *, int, int);

    for (int i = 0; i < n; ++i) {
        int e = A[1];
        B[i] = e;
        swap(A[1], A[n-i]);
        max_heap_delete(A, 1, n-i-1);
    }
}

void max_heap_delete(int *A, int i, int n)
{
    if (i > n || n <=1) return;
    //int e = A[1];
    int L = 2*i;
    int R = 2*i + 1;
    if(L > n) return;

    if (R > n) {
        if(A[L] > A[i])
            swap(A[L],A[i]);
        return;
    }
    //L R
    if (A[L]>A[R]) {
        if(A[L] > A[i]) {
            swap(A[L], A[i]);
            max_heap_delete(A,L,n);
        }
    } else{
        if(A[R] > A[i]) {
            swap(A[R], A[i]);
            max_heap_delete(A,R,n);
        }
    }

}


void Swap(int *A, int m, int n) {
	int temp = A[m];
	A[m] = A[n];
	A[n] = temp;
}
/*
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
        }
}
*/
