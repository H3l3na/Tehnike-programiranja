#include <iostream>
#include <new>
#include <stdexcept>
#include <cmath>
#include <vector>

using namespace std;

template  <typename Tip>

Tip *f(vector<Tip> v){
    Tip *novi=nullptr;
    try{
    novi=new Tip[v.size()];
    for (int i=v.size()-1, j=0; i>=0, j<v.size(); i--, j++){
        novi[j]=v[i];
    }
    return novi;
    }catch(...){
        delete [] novi;
    }
}

int main()
{
    vector<int> v={1,2,3,4,5};
    try{
        int *novi=f(v);
        for (int i=0; i<v.size(); i++){
            cout << novi[i] << " ";
        }
    }catch(...){
        throw "Neuspjela alokacija";
    }
    return 0;
}
