#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

struct Vrijeme{
    int sati, minute, sekunde;
    void IspisiVrijeme(int s, int m, int sek);
   // int SaberiVrijeme(Vrijeme v1, Vrijeme v2);
    void ispisiVrijeme();
};

void Vrijeme::IspisiVrijeme(int s, int m, int sek){
    cout << s << ":" << m << ":" << sek << endl;
}

void Vrijeme::ispisiVrijeme(){
    cout << setw(2)<<setfill('0')<< (*this).sati<< ":" << setw(2)<<setfill('0')<<(*this).minute<< ":" << setw(2)<<setfill('0')<<(*this).sekunde<< endl;
}

 Vrijeme SaberiVrijeme(Vrijeme v1, Vrijeme v2){
    Vrijeme v3;
    if (v1.sati+v2.sati>24){
        v3.sati=v1.sati+v2.sati-24;
    }else {
    v3.sati=v1.sati+v2.sati;}
    if (v1.minute+v2.minute>60){
        v3.sati+=1;
        v3.minute=v1.minute+v2.minute-60;
    }else{
    v3.minute=v1.minute+v2.minute;}
    if (v1.sekunde+v2.sekunde>60){
        v3.minute+=1;
        v3.sekunde=v1.sekunde+v2.sekunde-60;
    }else{
    v3.sekunde=v1.sekunde+v2.sekunde;}
    return v3;
}

int main()
{
    cout << "Hello world!" << endl;
    Vrijeme v;
    v.IspisiVrijeme(2, 30, 20);
    Vrijeme v1;
    Vrijeme v2;
    v1.sati=0;
    v1.minute=3;
    v1.sekunde=2;
    v2.sati=5;
    v2.minute=5;
    v2.sekunde=50;
    Vrijeme v3;
    v3=SaberiVrijeme(v1, v2);
    v3.ispisiVrijeme();
    return 0;
}
