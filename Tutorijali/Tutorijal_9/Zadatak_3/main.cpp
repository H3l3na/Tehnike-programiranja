#include <iostream>
#include <math.h>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Sat{
    int sati, minute, sekunde;
    static const int D=86400;
public:
    void Postavi(int sati, int minute, int sekunde);
    void Sljedeci(){/*
        if (sekunde==59){
            if (minute==59){
                sati++;
                minute=0;
                if (sati>=24){
                    sati=0;
                }
            }
            minute++;
            sekunde=0;
        }
        sekunde++;*/
        PomjeriZa(1);
    }
    void Prethodni(){
       /* if (sekunde==0){
            if (minute==0){
                sati--;
                minute=59;
            }
            sekunde=59;
        }
        sekunde--;*/
        PomjeriZa(-1);
    }
    void Ispisi() const {
        cout.fill('0'); cout.width(2); cout << sati << ":";
        cout.fill('0'); cout.width(2); cout << minute << ":";
        cout.fill('0'); cout.width(2); cout << sekunde;
    }
    /*void PomjeriZa(int pomak){
        if (sekunde+pomak>=60){
            if (pomak/60>=60){
                sati+=pomak/3600;
            }
            minute+=pomak/60;
            if (minute>=60){
                sati++;
                minute=minute%60;
            }
            sekunde+=pomak%60;
        }
    }*/
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
        int temp=sati*3600+minute*60+sekunde;
        temp+=pomak;
        if (temp < 0) temp = D + temp % D;
        if (temp>D){
            temp=temp%D;
        }
        SecsToHMS(temp, sati, minute, sekunde);
    }
    int DajSate() const{
        return sati;
    }
    int DajMinute() const{
        return minute;
    }
    int DajSekunde() const{
        return sekunde;
    }



};

void Sat::Postavi(int sati, int minute, int sekunde){
    if (sati<0 || minute <0 || sekunde <0 || sati>23 || minute >59 || sekunde>59){
        throw domain_error("Vrijeme nije u ispravnom opsegu.");
    }else{
        Sat::sati=sati;
        Sat::minute=minute;
        Sat::sekunde=sekunde;
    }
}
int BrojSekundiIzmedju(const Sat &s1, const Sat &s2){
        int br_s1, br_s2, br_s;
        br_s1=s1.sati*3600+s1.minute*60+s1.sekunde;
        br_s2=s2.sati*3600+s2.minute*60+s2.sekunde;
        br_s=br_s1-br_s2;
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
