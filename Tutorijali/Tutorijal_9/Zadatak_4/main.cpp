#include <iostream>
#include <math.h>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Sat{
    int sekunde;
    static const int D=86400;
public:
    void Postavi(int sati, int minute, int sekunde);
    void Sljedeci(){
        PomjeriZa(1);
    }
    void Prethodni(){
        PomjeriZa(-1);
    }
    void Ispisi() const {
        cout.fill('0'); cout.width(2); cout << sekunde/3600 << ":";
        cout.fill('0'); cout.width(2); cout << (sekunde%3600)/60 << ":";
        cout.fill('0'); cout.width(2); cout << (sekunde%3600)%60;
    }

    friend int BrojSekundiIzmedju(const Sat &s1, const Sat &s2);
    void SecsToHMS(int Secs, int &h, int &m, int &s) const {
        h=Secs/3600;
        m=(Secs%3600)/60;
        s=Secs%60;
        if (h>23){
            h=0;
        }
    }
    void PomjeriZa(int pomak){
        //Sta ako je pomak negativan?
        int temp=sekunde;
        temp+=pomak;
        if (temp < 0) temp = D + temp % D;
        if (temp>D){
            temp=temp%D;
        }
        SecsToHMS(temp, sati, minute, sekunde);
    }
    int DajSate() const{
        return sekunde/3600;
    }
    int DajMinute() const{
        return (sekunde%3600)/60;
    }
    int DajSekunde() const{
        return (sekunde%3600)%60;
    }



};

void Sat::Postavi(int sati, int minute, int sekunde){
    if (sati<0 || sati >23 || sekunde <0 || sekunde >59 || minute <0 || minute >59){
        throw domain_error("Neispravno vrijeme.");
    }
    else {
        Sat::sekunde+=sati*3600+minute*60+sekunde;
    }
}
int BrojSekundiIzmedju(const Sat &s1, const Sat &s2){
    int br_s;
    br_s=s1.sekunde-s2.sekunde;
        return br_s;
    }
using namespace std;

int main()
{
    Sat v;
    try{
        v.Postavi(10, 10, 10);
        cout << "Sati: " << v.DajSate() << endl;
        cout << "Minute: " << v.DajMinute() << endl;
        cout << "Sekunde: " << v.DajSekunde() << endl;
    }catch(...){
        cout << "Vrijeme nije u ispravnom opsegu. " << endl;
    }
    //cout << endl;
    cout << "Uvecano za jednu sekundu: " << endl;
    v.Sljedeci();
    v.Ispisi();
    //cout << endl;
    cout << "Umanjeno za jednu sekundu: " << endl;
    v.Prethodni();
    v.Ispisi();
    //cout << endl;
    Sat v1, v2;
    v1.Postavi(10, 10, 15);
    v2.Postavi(10, 10, 10);
    cout << "Broj sekundi izmedju vremena v1 i v2: " << BrojSekundiIzmedju(v1, v2) << endl;
    return 0;
}
