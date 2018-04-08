#include <iostream>
#include <new>
#include <stdexcept>
#include <math.h>

using namespace std;

int *f(int n){
    if (n<=0){
        throw "Broj elemenata mora biti pozitivan";
    }
    int *mat=nullptr;
    mat=new int[n];
    int i=0;
    try{
    for (i=0; i<n; i++){
        mat[i]=pow(2, i);
    }
    return mat;
    }catch(...){
        throw;
        delete [] mat;
    }
}

int main()
{
    int n;
    cout << "Unesite n: ";
    cin >> n;
    try{
        int *niz=f(n);
        for (int i=0; i<n; i++){
            cout << niz[i] << " ";
        }
        delete [] niz;
    }catch(...){
        cout << "Alokacija nije uspjela";
    }
    return 0;
}
