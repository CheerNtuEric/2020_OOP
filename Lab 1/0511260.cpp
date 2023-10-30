#include<iostream>
#include<string>
using namespace std;
 class matrix{

    private:

    public:
        double element[4];
        void MATprint();
};
void matrix :: MATprint(){
    cout << "[" << element[0] << ", " << element[1]<< ", " << element[2]<< ", " << element[3]<< "]"<<endl;
}
int main(){
    int n;
    double det;
    matrix mat1, mat2, mat3;
    char op;
    cin>>n;

    while(n--){
        cin >> op ;
        switch(op){
            case 'p':
                for(int i = 0 ; i < 4 ; i++)
                    cin>>mat1.element[i];
                mat1.MATprint();
                break;
            case '+':
                for (int i = 0 ; i < 4 ; i++)
                    cin >> mat1.element[i];
                for (int i = 0 ; i < 4 ; i++)
                    cin >> mat2.element[i];
                for (int i = 0 ; i < 4 ; i++)
                    mat1.element[i] += mat2.element[i];
                mat1.MATprint();
                break;
            case '*':
                for (int i = 0 ; i < 4 ; i++)
                    cin >> mat1.element[i];
                for (int i = 0 ; i < 4 ; i++)
                    cin >> mat2.element[i];
                mat3.element[0] = mat1.element[0] * mat2.element[0] + mat1.element[1] * mat2.element[2];
                mat3.element[1] = mat1.element[0] * mat2.element[1] + mat1.element[1] * mat2.element[3];
                mat3.element[2] = mat1.element[2] * mat2.element[0] + mat1.element[3] * mat2.element[2];
                mat3.element[3] = mat1.element[2] * mat2.element[1] + mat1.element[3] * mat2.element[3];
                mat3.MATprint();
                break;
            case 'd':
                for (int i = 0 ; i < 4 ; i++)
                    cin >> mat1.element[i];
                det = mat1.element[0] * mat1.element[3] - mat1.element[1] * mat1.element[2];
                cout << det << endl;
                break;
        }
    }
    return 0;
}
