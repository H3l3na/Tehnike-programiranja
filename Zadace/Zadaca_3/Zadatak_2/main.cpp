#include <iostream>
#include <iomanip>
#include <memory>
#include <new>
#include <stdexcept>
#include <iterator>
#include <map>
#include <functional>

using namespace std;

template <typename TipElemenata>

struct Matrica{
    int br_redova, br_kolona;
    TipElemenata** elementi=nullptr;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat){
    if (!mat.elementi) return;
    for (int i=0; i<mat.br_redova; i++){
        delete [] mat.elementi[i];
    }
    delete[] mat.elementi;
    mat.elementi=nullptr;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_red, int br_kol){
    Matrica<TipElemenata> mat;
    mat.br_redova=br_red;
    mat.br_kolona=br_kol;
    mat.elementi=new TipElemenata*[br_red];
    try{
        for (int i=0; i<br_kol; i++){
            mat.elementi[i]=new TipElemenata[br_kol];
        }
    }catch(...){
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename TipElemenata>

void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat){
    for (int i=0; i<mat.br_redova; i++){
        for (int j=0; j<mat.br_kolona; j++){
            cout << ime_matrice << " (" << i+1 << ", " << j+1 << ")= ";
            cin >> mat.elementi[i][j];
        }
    }
}

template <typename TipElemenata>

void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa ){
    for (int i=0; i<mat.br_redova; i++){
        for (int j=0; j<mat.br_kolona; j++){
            cout << setw(sirina_ispisa) << mat.elementi[i][j];
        }
        cout << endl;
    }
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2){
    if (m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona){
        throw domain_error("Matrice su nesaglasnih dimenzija!");
    }
    Matrica<TipElemenata> m3;
    m3=StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
    for (int i=0; i<m3.br_redova; i++){
        for (int j=0; j<m3.br_kolona; j++){
            m3.elementi[i][j]=m1.elementi[i][j]+m1.elementi[i][j];
        }
    }
    return m3;
}

template <typename TipElemenata>
void ProsiriPoFunkcijama(Matrica<TipElemenata> &mat, map<string, function<int(int)>> m){
    try{
            for (int i=mat.br_redova; i<2*mat.br_redova; i++){
                for (int j=0; j<mat.br_kolona; j++){
                        mat.elementi[i]=new TipElemenata[mat.br_kolona];
                }
            }
            for (int i=mat.br_redova; i<2*mat.br_redova; i++){
                for (int j=0; j<mat.br_kolona; j++){
                    mat.elementi[i][j]=0;
                }
            }
    }catch(...){
        UnistiMatricu(mat);
        throw;
    }
}

int main()
{
    std::map<std::string, std::function<int(int)>> mapa{
 {"dolje", [] (int x) { return x + 2; }}
};
    Matrica<double> a, b, c; // AUTOMATSKA INICIJALIZACIJA!!!
 int m, n;
 std::cout << "Unesi broj redova i kolona za matrice:\n";
 std::cin >> m >> n;
 try {
 a = StvoriMatricu<double>(m, n);
 b = StvoriMatricu<double>(m, n);
 std::cout << "Unesi matricu A:\n";
 UnesiMatricu('A', a);
 ProsiriPoFunkcijama(a, mapa);
 IspisiMatricu(a, 3);
 cout << endl;
 std::cout << "Unesi matricu B:\n";
 UnesiMatricu('B', b);
 std::cout << "Zbir ove dvije matrice je:\n";
 IspisiMatricu(c = ZbirMatrica(a, b), 7);
 }
 catch(std::bad_alloc) {
 std::cout << "Nema dovoljno memorije!\n";
 }
 UnistiMatricu(a); UnistiMatricu(b); UnistiMatricu(c);
 return 0;
}
