#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
using namespace std;

const double PI = atan(1)*4;

using namespace std;

class Ugao{
    int stepeni, minute, sekunde;
    void Domen (int &u){
        while (u<1296000){
            u+=1296000;
        }
        while (u>=1296000){
            u-=1296000;
        }
        Ugao::sekunde=u%60;
        u/=60;
        Ugao::minute=u%60;
        u/=60;
        Ugao::stepeni=u;
    }
public:
    Ugao(double radijani = 0){
        Postavi(radijani);
    }
    Ugao(int stepeni, int minute, int sekunde){
        Postavi(stepeni, minute, sekunde);
    }
    void Postavi(double radijani){
        int radijani1=radijani*(180*3600)/PI;
        Domen(radijani1);
    }
    void Postavi(int stepeni, int minute, int sekunde){
        int temp;
        temp=(stepeni*3600+minute*60+sekunde);
        Domen(temp);
    }
    double DajRadijane() const{
        int temp;
        temp=(stepeni*3600+minute*60+sekunde)*(PI/(180*3600));
        return temp;
    }
    void OcitajKlasicneJedinice(int &stepeni, int &minute, int &sekunde){
        stepeni=Ugao::stepeni;
        minute=Ugao::minute;
        sekunde=Ugao::sekunde;
    }
    int DajStepene() const{
        return stepeni;
    }
    int DajMinute() const{
        return minute;
    }
    int DajSekunde() const{
        return sekunde;
    }
    void Ispisi() const{
        cout << this->DajRadijane() << "rad" << endl;
    }
    void IspisiKlasicno() const{
        cout << stepeni << "deg " << minute << "min " << sekunde << "sec "  << endl;
    }
    Ugao &SaberiSa(const Ugao &u){
        this->stepeni+=u.stepeni;
        this->minute+=u.minute;
        this->sekunde+=u.sekunde;
        int temp((stepeni * 3600) + (minute * 60) + sekunde);
        Domen(temp);
        return *this;
    }
    Ugao &PomnoziSa(double x){
    this->stepeni*=x;
    this->minute*=x;
    this->sekunde*=x;
    int temp((stepeni * 3600) + (minute * 60) + sekunde);
    Domen(temp);
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1, const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u, double x);
};

Ugao ZbirUglova (const Ugao &u1, const Ugao &u2){
    Ugao u3;
    u3.stepeni=u1.stepeni+u2.stepeni;
    u3.minute=u1.minute+u2.minute;
    u3.sekunde=u1.sekunde+u2.sekunde;
    return u3;
}

Ugao ProduktUglaSaBrojem(const Ugao &u, double x){
    Ugao u3;
    u3.stepeni=u.stepeni*x;
    u3.minute=u.minute*x;
    u3.sekunde=u.sekunde*x;
    return u3;
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
