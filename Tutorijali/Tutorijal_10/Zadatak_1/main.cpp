#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
using namespace std;

const double PI = atan(1)*4;

using namespace std;

class Ugao{
    double radijani;
    void Domen (double &u){
        while (u<0){
            u+=2*PI;
        }
        while (u>=(2*PI)){
            u-=2*PI;
        }
    }
public:
    Ugao(double radijani = 0){
        Ugao::radijani=radijani;
    }
    Ugao(int stepeni, int minute, int sekunde){
        int temp;
        temp=stepeni*3600+minute*60+sekunde;
        Ugao::radijani=(temp*PI)/3600;
        Domen(Ugao::radijani);
    }
    void Postavi(double radijani){
        Ugao::radijani=radijani;
    }
    void Postavi(int stepeni, int minute, int sekunde){
        int temp;
        temp=(stepeni*3600+minute*60+sekunde);
        Ugao::radijani=(temp*PI)/(180*3600);
        Domen(Ugao::radijani);
    }
    double DajRadijane() const{
        return radijani;
    }
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
        int temp=radijani;
        temp=radijani* (180*3600)/PI;
        sekunde=temp%60;
        temp/=60;
        minute=temp%60;
        temp/=60;
        stepeni=temp;
    }
    int DajStepene() const{
        return static_cast<int>((radijani * (180 * 3600) / PI) / 60);
    }
    int DajMinute() const{
        return static_cast<int>((radijani * (180 * 3600) / PI) / 60) % 60;
    }
    int DajSekunde() const{
        return static_cast<int>(radijani * (180 * 3600) / PI) % 60;
    }
    void Ispisi() const{
        cout << radijani << "rad" << endl;
    }
    void IspisiKlasicno() const{
        int temp=radijani* (180*3600)/PI;
        int sekunde, minute, stepeni;
        sekunde=temp%60;
        temp/=60;
        minute=temp%60;
        temp/=60;
        stepeni=temp;
        cout << stepeni << "deg " << minute << "min " << sekunde << "sec " << endl;
    }
    Ugao &SaberiSa(const Ugao &u){
        Ugao::radijani += u.radijani;
        Domen(Ugao::radijani);
        return *this;
    }
    Ugao &PomnoziSa(double x){
    Ugao::radijani*=x;
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova (const Ugao &u1, const Ugao &u2){
    Ugao u3;
    u3.radijani=u1.radijani+u2.radijani;
    return u3;
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
    return u.radijani*x;
}
int main()
{
    Ugao alpha(20), beta(55, 22, 33);
    // Testiranje OcitajKlasicneJedinice i IspisiKlasicno:
    int st, mi, se;
    beta.OcitajKlasicneJedinice(st, mi, se);
    std::cout << st << "deg " << mi << "min " << se << "sec " << "== ";
    beta.IspisiKlasicno();
    // Testiranje PomnoziSa i Ispisi:
    alpha.PomnoziSa(2);
    alpha.Ispisi();
    alpha.SaberiSa(beta);
    alpha.Ispisi();
    // Testiranje funkcija Postavi:
    alpha.Postavi(10);
    beta.Postavi(10, 10, 10);
    // Testiranje ZbirUglova i ProduktUglaSaBrojem
    Ugao gama(ZbirUglova(alpha, beta));
    gama.Ispisi();
    gama=ProduktUglaSaBrojem(beta, 2);
    gama.IspisiKlasicno();
    return 0;
}
