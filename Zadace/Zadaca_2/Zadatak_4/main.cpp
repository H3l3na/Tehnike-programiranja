#include <iostream>
#include <new>
#include <vector>

using namespace std;

template <typename t>

t **AlocirajKontinualno(vector<t> &v, int koliko_puta){
    t **mat=nullptr;
    int br_el(0);
    for (int i=0; i<v.size(); i++){
        br_el+=v[i];
    }
    br_el=br_el*koliko_puta;
    try{
        mat=new int*[v.size()*koliko_puta] {};
        int s=0;
        for (int i=0; i<v.size(); i++){
            s+=v[i];
        }
        mat[0]=new int[s*koliko_puta];
        int *niz=new int[br_el*koliko_puta];
        for (int i=1; i<v.size()*koliko_puta; i++){
            mat[i]=mat[i-1]+v[(i-1)%v.size()];
        }
       /* for (int k=0; k<koliko_puta; k++){
            for (int i=v.size()-1; i>=0; i--){
                for (int j=v[i]-1; j>=0; j--){
                    if (i==j){
                        mat[i][j]=1;
                    }else{
                        mat[i][j]=v[i]-j;
                    }
                }
            }
        }*/

        for (int i=0; i<v.size()*koliko_puta; i++){
            for (int j=0; j<v[i%v.size()]; j++){
                if (j==0){
                    mat[i][j]=v[i%v.size()];
                }else {
                    mat[i][j]=mat[i][j-1]-1;
                }
            }
        }
        return mat;
    }catch(...){
        if (mat!=nullptr){
            for (int i=0; i<v.size()*koliko_puta; i++){
            delete [] mat[i];
            }
            delete [] mat;
        }
        throw "Nema dovoljno memorije";
    }
}

template <typename t>

t **AlocirajFragmentirano(vector<t> &v, int koliko_puta){
    t maks=v[0];
    for (int i=0; i<v.size(); i++){
        if (v[i]>maks){
            maks=v[i];
        }
    }
    t **mat=nullptr;
    try{
        mat=new int*[v.size()*koliko_puta];
        for (int i=0; i<v.size()*koliko_puta; i++){
            mat[i]=nullptr;
        }
        try{
           // for (int k=0; k<koliko_puta; k++){
                for (int i=0; i<v.size()*koliko_puta; i++){
                    mat[i]=new int[v[i%v.size()]];
                }
          //  }
           for (int k=0; k<koliko_puta; k++){
                for (int i=0; i<v.size(); i++){
                    t maks2=maks;
                    for (int j=v[i]; j>0; j--){
                        mat[i][j]=maks2;
                        maks2--;
                    }
                }
           }
            return mat;
        }catch(...){
            for (int i=0; i<v.size()*koliko_puta; i++){
                delete [] mat[i];
            }
            delete [] mat;
            throw "Poruka za try";
        }
    }catch(...){
        throw "Neuspjela alokacija";
    }
}

template <typename t>

t **KreirajPoUvrnutomPravilu(vector<t> &v, int koliko_puta, bool fragmentirano=true){
    for (int i=0; i<v.size(); i++){
        if (v[i]<=0) throw "Neispravan vektor.";
    }
    t maks=v[0];
    for (int i=0; i<v.size(); i++){
        if (v[i]>maks){
            maks=v[i];
        }
    }
    int p;
    int period;
    bool periodican;
    t **mat=nullptr;
    for (int i=1; i<v.size(); i++){
        if (v[0]==v[i]){
            p=i; break;
        }
    }
    if (p>=2){
        periodican=true;
        period=p;

    }
    for (int i=0; i<v.size()-p, p<v.size(); i++){
        if (v[i]!=v[p]){
            periodican=false;
            break;
        }
       p++;
    }
    if (periodican==true){
        v.resize(period);
    }else {
        maks+=1;
        for (int i=0; i<v.size(); i++){
            v[i]=maks-v[i];
        }
    }
    if (fragmentirano==true){
        try{
           mat=AlocirajFragmentirano(v, koliko_puta);
           return mat;
        }catch(const char* poruka){
            cout << "Izuzetak: " << poruka;
        }
    }
    else if (fragmentirano==false){
        try{
           mat=AlocirajKontinualno(v, koliko_puta);
           return mat;
        }catch(const char* poruka){
            cout << "Izuzetak: " << poruka;
        }
    }
}

int main() {
    std::cout << "Unesite velicinu vektora: ";
    int n;
    cin >> n;
    vector<int> v;
    cout << "Unesite elemente vektora: ";
    int broj;
    for (int i=0; i<n; i++){
        cin >> broj;
        v.push_back(broj);

    }
    int koliko_puta;
    cout << "Unesite broj ponavljanja: ";
    cin >> koliko_puta;
    int f;
    bool fragmentirano;
    cout << "Odaberite alokaciju: 1 - fragmentirana, 0 - kontinualna: ";
    cin >> f;
    if (f==1){
        fragmentirano=true;
    }else if (f==0)
    {
        fragmentirano=false;
    }
    if (fragmentirano==false){
        try{
            int **mat=KreirajPoUvrnutomPravilu(v, koliko_puta, fragmentirano);
            for (int k=0; k<koliko_puta; k++){
                for (int i=0; i<v.size(); i++){
                    for (int j=0; j<v[i]; j++){
                        cout << mat[i][j] << "   ";
                    }
                    cout << endl;
                }
            }
            for (int i=0; i<koliko_puta; i++){
            delete [] mat[i];

            }
            delete [] mat;
        }catch(const char* poruka){
            cout << poruka;
        }
    }else if (fragmentirano==true){
        try{
            int **mat=KreirajPoUvrnutomPravilu(v, koliko_puta, fragmentirano);
            for (int k=0; k<koliko_puta; k++){
                for (int i=0; i<v.size(); i++){
                    for (int j=1; j<=v[i]; j++){
                        cout << mat[i][j] << "   ";
                    }
                    cout << endl;
                }
            }
            for (int i=0; i<v.size()*koliko_puta; i++){
            delete [] mat[i];
            }
            delete [] mat;
            /*for (int i=0; i<koliko_puta; i++){
            delete [] mat;
            }*/
        }catch(const char* poruka){
            cout << poruka;
        }
    }
    return 0;
}
