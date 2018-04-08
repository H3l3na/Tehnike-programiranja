#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Tim{
    char ime[20];
    int broj_odigranih, broj_pobjeda, broj_nerijesenih, broj_poraza, broj_datih, broj_primljenih, broj_poena;
public:
    Tim(const char ime[]){
        if (strlen(ime)>19){
            throw domain_error("Predugo ime!");
        }else {
            strcpy(Tim::ime, ime);
        }

        broj_odigranih=0, broj_pobjeda=0, broj_nerijesenih=0, broj_poraza=0, broj_datih=0, broj_primljenih=0, broj_poena=0;
    }
    void ObradiUtakmicu(int broj_datih, int broj_primljenih){
        int i=0, brojac=0;
        if (broj_datih<0 || broj_primljenih<0){
            throw domain_error("Greska");
        }
        if (broj_datih==broj_primljenih){
            broj_nerijesenih++;
            broj_poena++;
        }
        else if (broj_datih>broj_primljenih){
            broj_pobjeda++;
            broj_poena+=3;
        }
        else if (broj_datih<broj_primljenih){
            broj_poraza++;
        }
    }
    const char *DajImeTima() const{
        return ime;
    }
    int DajBrojPoena() const{
        return broj_poena;
    }
    int DajGolRazliku() const{
        return abs(broj_primljenih-broj_datih);
    }
    void IspisiPodatke() const{
        cout << setw(20) << left << ime;
        cout << setw(4) << right << broj_odigranih;
        cout << setw(4) << right << broj_pobjeda;
        cout << setw(4) << right << broj_nerijesenih;
        cout << setw(4) << right << broj_poraza;
        cout << setw(4) << right << broj_datih;
        cout << setw(4) << right << broj_primljenih;
        cout << setw(4) << right << broj_poena << endl;
    }
};



int main()
{
    try{
        Tim t1("Zeljeznicar"), t2("Sarajevo");
        t1.ObradiUtakmicu(0,0);
        t2.ObradiUtakmicu(0,0);
        t1.IspisiPodatke();
        t2.IspisiPodatke();
    }catch(domain_error izuzetak){
        cout << izuzetak.what() << endl;
    }
    return 0;
}
