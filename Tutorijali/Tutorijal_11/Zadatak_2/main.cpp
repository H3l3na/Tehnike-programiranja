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
    friend class Liga;
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

class Liga{
    int broj_timova;
    const int max_broj_timova;
    Tim **timovi=nullptr;
public:
    explicit Liga(int velicina_lige): max_broj_timova(velicina_lige), broj_timova(0){
        timovi=new Tim*[velicina_lige]{};
    }
    explicit Liga(std::initializer_list<Tim> lista_timova): max_broj_timova(lista_timova.size()), broj_timova(lista_timova.size()){
    int i=0;
    for (i=0; i<broj_timova; i++){
        timovi[i]=new Tim(*(lista_timova.begin()+i));
    }
    }
    ~Liga();
    Liga(const Liga &l);
    Liga(Liga &&l);
    Liga &operator =(const Liga &l);
    Liga &operator =(Liga &&l);
    void DodajNoviTim(const char ime_tima[]){
        if (broj_timova==max_broj_timova){
            throw domain_error("Nema vise mjesta.");
        }
        timovi[broj_timova]=new Tim(ime_tima);
        broj_timova++;
    }
    void RegistrirajUtakmicu(const char tim1[], const char tim2[],
    int rezultat_1, int rezultat_2);
    void IspisiTabelu();
    /*bool sortiraj(Tim* t1, Tim* t2){
        if (t1->DajBrojPoena()>t2->DajBrojPoena()){
            return true;
        }
        else if (t2->DajBrojPoena()>t1->DajBrojPoena()){
            return false;
        }else if (t1->DajBrojPoena()==t2->DajBrojPoena()){
            if (t1->DajGolRazliku()>t2->DajGolRazliku()){
                return true;
            }else if (t2->DajGolRazliku()>t1->DajGolRazliku()){
                return false;
            }
        }
    }*/
     struct sorter {
    bool operator() (Tim *t1, Tim *t2) {if(t1->DajBrojPoena()>t2->DajBrojPoena()) return true;
    else if(t1->DajBrojPoena()<t2->DajBrojPoena()) return false;
    else {if(t1->DajGolRazliku()>t2->DajGolRazliku()) return true;
    else return false; } }
    };
};

Liga::~Liga(){
    if (timovi!=nullptr){
        for (int i=0; i<broj_timova; i++){
            delete timovi[i];
        }
        delete [] timovi;
    }
}

Liga::Liga(const Liga &l):
    broj_timova(l.broj_timova),
    timovi(new Tim*[l.max_broj_timova]{}),
    max_broj_timova(l.max_broj_timova){
    for (int i=0; i<l.broj_timova; i++){
        timovi[i]=new Tim(*l.timovi[i]);
    }
}

void Liga::IspisiTabelu(){
    int i=0;
    sort(timovi+0, timovi+broj_timova, sorter());
    for (i=0; i<broj_timova; i++){
        timovi[i]->IspisiPodatke();
    }
}

void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[],
    int rezultat_1, int rezultat_2){
        int i=0;
        int brojac1=0, brojac2=0, indeks1, indeks2;
        for (i=0; i<broj_timova; i++){
            if (strcmp(tim1, timovi[i]->DajImeTima())==0){
                brojac1=1;
                indeks1=i;
            }
        }
        for (i=0; i<broj_timova; i++){
            if (strcmp(tim2, timovi[i]->DajImeTima())==0){
                brojac2=1;
                indeks2=i;
            }
        }
        if (brojac1==0 && brojac2!=0){
            throw domain_error ("Tim 1 ne postoji");
        }
        else if (brojac2==0 && brojac1!=0){
            throw domain_error ("Tim 2 ne postoji");
        }else if (brojac1==0 && brojac2==0){
            throw domain_error ("Navedeni timovi ne postoje.");
        }else{
        timovi[indeks1]->ObradiUtakmicu(rezultat_1, rezultat_2);
        timovi[indeks2]->ObradiUtakmicu(rezultat_1, rezultat_2);
        }
    }

Liga::Liga(Liga &&l): broj_timova(l.broj_timova), max_broj_timova(l.max_broj_timova), timovi(l.timovi){
    l.timovi=nullptr,
    l.broj_timova=0;
}

Liga &Liga::operator=(const Liga &l){
    if (l.max_broj_timova!=max_broj_timova){
        cout << "Broj timova razlicit";
    }
    if (&l!=this){
        for (int i=0; i<broj_timova; i++){
            delete timovi[i];
        }
        for (int i=0; i<l.broj_timova; i++){
            timovi[i]=new Tim(*l.timovi[i]);
        }
    }
    return *this;
}

Liga &Liga::operator=(Liga &&l){
    if (l.max_broj_timova!=max_broj_timova){
        cout << "Razlicit broj timova";
    }
    if (&l!=this){
        for (int i=0; i<broj_timova; i++){
            delete timovi[i];
        }
        delete [] timovi;
        timovi=l.timovi;
        broj_timova=l.broj_timova;
        l.timovi=nullptr;
        l.broj_timova=0;
    }
    return *this;
}
int main()
{
    try{
        Liga LigaPrvaka(4);
        LigaPrvaka.DodajNoviTim("Zeljeznicar");
        LigaPrvaka.DodajNoviTim("Manchester United");
        LigaPrvaka.DodajNoviTim("Valencia");
        LigaPrvaka.DodajNoviTim("Juventus");

        Liga LigaSampiona(16);

        LigaPrvaka.RegistrirajUtakmicu("Zeljeznicar", "Juventus", 1, 0);
        LigaPrvaka.RegistrirajUtakmicu("Juventus", "Zeljeznicar", 0, 0);
        LigaPrvaka.RegistrirajUtakmicu("Manchester United", "Valencia",1 ,1);
        LigaPrvaka.RegistrirajUtakmicu("Valencia", "Manchester United", 0, 1);
        LigaPrvaka.IspisiTabelu();

    }catch(const std::exception &izuzetak){
        cout << izuzetak.what() << endl;
    }
    return 0;
}
