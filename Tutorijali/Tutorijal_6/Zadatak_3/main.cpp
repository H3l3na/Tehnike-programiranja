#include <iostream>
#include <iomanip>
#include <new>
#include <stdexcept>

using namespace std;

int **DinamickaAlokacija(int n){
    int** mat=nullptr;
    try{
        mat=new int*[n];
        for (int i=0; i<n; i++){
            mat[i]=nullptr;
        }
        for (int i=0; i<n; i++){
            mat[i]=new int[2*i+1];
        }
        for (int i=0; i<n; i++){
            for (int j=0; j<2*i+1; j++){
            if (j==0 || j==2*i){
                mat[i][j]=1;
            }else if (j<i){
                mat[i][j]=mat[i-1][j];
            }else{
                mat[i][j]=mat[i-1][j-1]+1;
            }
            }
        }
        return mat;
    }catch(...){
        for (int i=0; i<n; i++){
            delete mat[i];
        }
        delete [] mat;
        throw;
    }
}

int main()
{
    int n;
    cout << "Unesite n: " << endl;
    cin >> n;
    try{
        int **mat=DinamickaAlokacija(n);
        for (int i=0; i<n; i++){
            for (int j=0; j<2*i+1; j++){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        delete [] mat[0];
        delete [] mat;
    }catch(...){
        cout << "Nije uspjela alokacija";
    }
    return 0;
}
