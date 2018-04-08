#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

vector<vector<double> > EkspanzijaMatrice (vector<vector<double> > mat, int p, int q){
        if (p<=0 || q<=0) throw domain_error("Nelegalni parametri");
        vector<vector<double> > mat1;
        int broj_redova;
        int broj_kolona;
        broj_redova=mat.size();
        broj_kolona=mat[0].size();
        mat1.resize(p*broj_redova);
        for (int i=0; i<mat.size(); i++){
                if (mat[i].size()!=mat[0].size()) throw domain_error("Nekorektna matrica");
        }
        for (int i=0; i<mat1.size(); i++){
                mat1[i].resize(q*broj_kolona);
        }
        for (int i=0; i<mat1.size(); i++){
                for (int j=0; j<mat1[i].size(); j++){
                        mat1[i][j]=mat[i/p][j/q];
                }
        }
        return mat1;
}
int main() {
        std::cout << "Unesite dimnezije matrice (mxn): " << endl;
        int m, n;
        cin >> m;
        cin >> n;
        vector<vector<double> > mat;
        mat.resize(m);
        for (int i=0; i<mat.size(); i++){
                mat[i].resize(n);
        }
        int broj;
        cout << "Unesite elemente matrice: " << endl;
        for (int i=0; i<mat.size(); i++){
                for (int j=0; j<mat[0].size(); j++){
                        cin >> broj;
                        mat[i][j]=broj;
                }
        }
        cout << "Unesite p i q: " << endl;
        int p, q;
        cin >> p;
        cin >> q;
        vector<vector<double> > mat1;
        try {
        mat1=EkspanzijaMatrice(mat, p, q);
        } catch(domain_error izuzetak){
                cout << izuzetak.what() << endl;
        }
        cout << "Prosirena matrica glasi: " << endl;
        for (int i=0; i<mat1.size(); i++){
                for (int j=0; j<mat1[i].size(); j++){
                        cout << mat1[i][j] << " ";
                }
                cout << endl;
        }
        return 0;
}
