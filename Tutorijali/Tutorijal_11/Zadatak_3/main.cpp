#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <vector>
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
    vector<Tim*> timovi;
    static bool FunKriterija(Tim* t1, Tim* t2);
    void AlocirajNiz(int br);
    void OslobodiTimove();
    int PronadjiTim(const char* ime_tima)const;
public:
    explicit Liga();
    explicit Liga(std::initializer_list<Tim> lista_timova);
    ~Liga();
    Liga(const Liga &l);
    Liga(Liga &&l);
    Liga &operator =(const Liga &l);
    Liga &operator =(Liga &&l);
    void DodajNoviTim(const char ime_tima[]);
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

};

int Liga::PronadjiTim(const char* ime_tima) const {
    for (int i=0; i<timovi.size(); i++){
        if (strcmp(ime_tima, timovi[i]->DajImeTima())==0){
            return i;
        }
    }
    return -1;
}

void Liga::DodajNoviTim(const char ime_tima[]){
    if (PronadjiTim(ime_tima)!=-1){
        throw domain_error("Tim vec postoji!");
    }
    try{
        timovi[timovi.size()]=new Tim(ime_tima);
    }catch(bad_alloc){
        throw domain_error ("Neuspjela alokacija");
    }catch(...){
        throw domain_error ("tim vec postoji");
    }
}
bool Liga::FunKriterija(Tim* t1, Tim *t2){
    if (t1->DajBrojPoena()>t2->DajBrojPoena()){
        return true;
    }else if(t1->DajBrojPoena()<t2->DajBrojPoena()){
        return false;
    }else if (t1->DajBrojPoena()==t2->DajBrojPoena()){
        if (t1->DajGolRazliku()>t2->DajGolRazliku()){
            return true;
        }else if (t1->DajGolRazliku()<t2->DajGolRazliku()){
            return false;
        }
    }
}

void Liga::AlocirajNiz(int br){
    try{
        timovi.emplace_back(new Tim*[br]);

    }catch(...){
        OslobodiTimove();
        throw;
    }
}

void Liga::OslobodiTimove(){
    for (int i=0; i<timovi.size(); i++){
        delete timovi[i];
    }
}

Liga::~Liga(){
        for (int i=0; i<timovi.size(); i++){
            delete timovi[i];
        }

}
/*
Liga::Liga(const Liga &l):
    broj_timova(l.broj_timova),
    timovi(new Tim*[l.max_broj_timova]{}),
    max_broj_timova(l.max_broj_timova){
    for (int i=0; i<l.broj_timova; i++){
        timovi[i]=new Tim(*l.timovi[i]);
    }
}*/

void Liga::IspisiTabelu(){
    int i=0, broj_timova=timovi.size();
    sort(timovi, timovi+broj_timova, FunKriterija);
    for (i=0; i<timovi.size(); i++){
        timovi[i]->IspisiPodatke();
    }
}

void Liga::RegistrirajUtakmicu(const char tim1[], const char tim2[],
    int rezultat_1, int rezultat_2){
         if(PronadjiTim(tim1) == -1 || PronadjiTim(tim2) == -1)
        throw std::domain_error("Jedan ili oba tima se ne nalaze u ligi!");
        timovi[PronadjiTim(tim1)]->ObradiUtakmicu(rezultat_1, rezultat_2);
        timovi[PronadjiTim(tim2)]->ObradiUtakmicu(rezultat_1, rezultat_2);

    }

Liga::Liga(Liga &&l): timovi.size(l.timovi(size)), max_broj_timova(l.max_broj_timova), timovi(l.timovi){
    l.timovi=nullptr,
    l.broj_timova=0;
}

Liga::Liga(const std::initializer_list<Tim> lista_timova) :
    timovi.size(lista_timova.size()),
    timovi(nullptr) {
    int brojac(0);
    try {
        for(const auto &x : lista_timova)
            timovi[brojac++] = new Tim(x);
    }
    catch(...) {
        OslobodiTimove();
        throw; // prosljedjujemo izuzetak ..
    }
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
