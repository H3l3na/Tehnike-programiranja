#include <iostream>
#include <vector>
#include <new>
using namespace std;

bool savrsen(int n){
    int suma(0);
    for (int i=1; i<n; i++){
        if (n%i==0){
            suma+=i;
        }
    }
    if (n==suma){
        return true;
    }
    return false;
}

template <typename t>

t *funkcija(vector<t> &v){
    t* p=nullptr;
    int brojac(0);
    for (int i=0; i<v.size(); i++){
        int suma(0);
        for (int i=1; i<v[i]; i++){
            if (v[i]%i==0){
                suma+=v[i];
            }
        }
        if (suma==v[i]){
            brojac++;
        }
    }
    try{
        p=new int [brojac];
        for (int i=0; i<v.size(); i++){
            if (savrsen(v[i])==true){
                p[i]=v[i];
            }
        }
        return p;
    }catch(...){
        delete [] p;
        throw "Greska prilikom alokacije";
    }
}

int brojDjelioca(int n){
    int brojac(0);
    for (int i=1; i<n; i++){
        if (n%i==0){
            brojac++;
        }
    }
    return brojac;
}

void modificiraj(vector<int> &v){
    int broj;
    for (int i=0; i<v.size()-1; i++){
            for (int j=i+1; j<v.size()-1; j++){
                if (brojDjelioca(v[i])==brojDjelioca(v[j])){
                    v[i]=v[v.size()-1];
                    v[i+1]=v[v.size()-2];
                    v.resize(v.size()-2);
                    broj=brojDjelioca(v[i-1]);
                    i--;
                }
                if (v[j]==broj){
                    v[j]=v[j+1];
                    v.resize(v.size()-1);

                }
            }
    }
}

int main()
{
    cout << "Unesite velicinu vektora: " << endl;
    int n;
    cin >> n;
    int broj;
    vector<int> v;
    cout << "Unesite elemente vektora: " << endl;
    for (int i=0; i<n; i++){
        cin >> broj;
        v.push_back(broj);
    }
    int broj_savrsenih(0);
    for (int i=0; i<v.size(); i++){
        int suma(0);
        for (int j=1; j<v[i]; j++){
            if (v[i]%j==0){
                suma+=j;
            }
        }
        if (v[i]==suma){
            broj_savrsenih++;
        }
    }
    modificiraj(v);
    cout << "Sada vektor glasi: " << endl;
    for (int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    try{
        int *p=funkcija(v);
        for (int i=0; i<broj_savrsenih; i++){
            cout << p[i] << " ";
        }
        delete []p;
    }catch(...){
        cout << "Greska prilikom alokacije";
    }
    return 0;
}
