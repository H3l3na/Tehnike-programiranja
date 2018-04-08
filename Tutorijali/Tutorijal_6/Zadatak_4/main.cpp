#include <iostream>
#include <new>
#include <iomanip>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename Tip>

Tip **DinamickaAlokacija(vector<vector<Tip>> v){
    Tip **novi=nullptr;
    try{
        novi=new Tip*[v.size()];
        for (int i=0; i<v.size(); i++){
            novi[i]=nullptr;}
        try{

        for (int i=0; i<v.size(); i++){
            novi[i]=new Tip[v[i].size()];
        }
        for (int i=0; i<v.size(); i++){
            for (int j=0; j<v[i].size(); j++){
                novi[i][j]=v[i][j];
            }
        }
    return novi;
    }catch(...){
        for (int i=0; i<v.size(); i++){
            delete novi[i];
        }
        delete [] novi;
        throw;
    }
    }catch(bad_alloc){
        throw "Nije uspjela alokacija";
    }
}

int main()
{
    int m, n;
    cout << "Unesite dimenzije matrice n: " << endl;
    cin >> n;
    cout << "Unesite m: " << endl;
    cin >> m;
    vector<vector<int>> v;
    v.resize(n);
    for (int i=0; i<n; i++){
        v[i].resize(m);
    }
    cout << "Unesite matricu: " << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> v[i][j];
        }
    }
    try{
        int** mat=DinamickaAlokacija(v);
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }catch(char* poruka){
        cout << poruka << endl;
    }catch(bad_alloc poruka){
        cout << poruka.what() << endl;
    }
    return 0;
}
