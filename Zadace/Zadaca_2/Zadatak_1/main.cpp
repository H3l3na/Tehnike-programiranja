#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>


using namespace std;

bool aktivan=true;

void AktivirajRobota(){
    if (aktivan==false){
        aktivan=true;
    }
}
void DeaktivirajRobota(){
    if (aktivan==true){
        aktivan=false;
    }
}

enum class Smjer {Nalijevo, Nadesno};
enum class Pravci {Sjever, Istok, Jug, Zapad};
enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar,
 NeispravanParametar};
enum class Komande {Aktiviraj, Deaktiviraj, Nalijevo, Nadesno, Idi, Kraj};


void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu);
void Idi(int &x, int &y, Pravci orijentacija, int korak);
void IspisiPoziciju(int x, int y, Pravci orijentacija);
void PrijaviGresku(KodoviGresaka kod_greske);
void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija);


bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske);

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija){
    if (komanda==Komande::Aktiviraj){
        AktivirajRobota();
    }else if (komanda==Komande::Deaktiviraj){
        DeaktivirajRobota();
    }else if (komanda==Komande::Idi){
        Idi(x, y, orijentacija, parametar);
    }else if (komanda==Komande::Nadesno){
        Rotiraj(orijentacija, Smjer::Nadesno);
    }else if (komanda==Komande::Nalijevo){
        Rotiraj(orijentacija, Smjer::Nalijevo);
    }else if (komanda==Komande::Kraj){
        cout << "Dovidjenja!";
    }
}

void Rotiraj(Pravci &orijentacija, Smjer na_koju_stranu){
    if (aktivan==true){
    if (na_koju_stranu==Smjer::Nalijevo){
            if (orijentacija==Pravci::Sjever){
                orijentacija=Pravci::Zapad;
            }else if (orijentacija==Pravci::Zapad){
                orijentacija=Pravci::Jug;
            }else if (orijentacija==Pravci::Jug){
                orijentacija=Pravci::Istok;
            }else if (orijentacija==Pravci::Istok){
                orijentacija=Pravci::Sjever;
            }
    }else if (na_koju_stranu==Smjer::Nadesno){
        if (orijentacija==Pravci::Sjever){
            orijentacija=Pravci::Istok;
        }else if (orijentacija==Pravci::Istok){
            orijentacija=Pravci::Jug;
        }else if (orijentacija==Pravci::Jug){
            orijentacija=Pravci::Zapad;
        }else if (orijentacija==Pravci::Zapad){
            orijentacija=Pravci::Sjever;
        }
    }
    }
}

void IspisiPoziciju(int x, int y, Pravci orijentacija){
    string pr;
    if (orijentacija==Pravci::Istok){
        pr="istok";
    }else if (orijentacija==Pravci::Zapad){
        pr="zapad";
    }else if (orijentacija==Pravci::Jug){
        pr="jug";
    }else if (orijentacija==Pravci::Sjever){
        pr="sjever";
    }
    if (aktivan==true){
        cout << "Robot je trenutno aktivan, nalazi se na poziciji " << "(" << x << "," << y << ") i gleda na " << pr << "." << endl;
    }else if (aktivan==false){
        cout << "Robot je trenutno neaktivan, nalazi se na poziciji " << "(" << x << "," << y << ") i gleda na " << pr << "." << endl;
    }
}

void PrijaviGresku(KodoviGresaka kod_greske){
    if (kod_greske==KodoviGresaka::PogresnaKomanda){
        cout << "Pogresna komanda. ";
    }else if(kod_greske==KodoviGresaka::NedostajeParametar){
        cout << "Nedostaje parametar. ";
    }else if (kod_greske==KodoviGresaka::SuvisanParametar){
        cout << "Suvisan parametar. ";
    }else if (kod_greske==KodoviGresaka::NeispravanParametar){
        cout <<  "Neispravan parametar. ";
    }
}

void Idi(int &x, int &y, Pravci orijentacija, int korak){
    if (aktivan==true){
    if (orijentacija==Pravci::Sjever){
        y+=korak;
    }else if (orijentacija==Pravci::Jug){
        y-=korak;
    }else if (orijentacija==Pravci::Istok){
        x+=korak;
    }else if (orijentacija==Pravci::Zapad){
        x-=korak;
    }
    }
}

int main()
{
    cout << "Robot je trenutno aktivan, nalazi se na poziciji (0,0) i gleda na sjever." << endl;
    char a='A';
    Pravci orijentacija(Pravci::Sjever);
    Smjer sm(Smjer::Nalijevo);
    Komande komanda;
    KodoviGresaka greska;
    char s;
    int b=0;
    int x=0, y=0;
    string status;
    if (aktivan==true){
        status="aktivan";
    }else if (aktivan==false){
        status="neaktivan";
    }
    while (a!='K'){
        cout << "Unesi komandu: ";
        cin >> a;
        if (a!='K' && a!='A' && a!='L' && a!='D' && a!='I'){
    while (a!='K' && a!='A' && a!='L' && a!='D' && a!='I'){
        cout << "Pogresan parametar. Molimo ponovite unos. " << endl;
        cin.ignore(10000, '\n');
        continue;
    }
    }
    if (a=='A'){
        cin >> s;
        if (s=='+'){
            komanda=Komande::Aktiviraj;
        }else if (s=='-'){
            komanda=Komande::Deaktiviraj;
        }
        if (cin.peek()!=0){
            greska=KodoviGresaka::SuvisanParametar;
            PrijaviGresku(greska);
            continue;
        }
        IzvrsiKomandu(komanda, b, x, y, orijentacija);
        IspisiPoziciju(x, y, orijentacija);
    }
    if (a=='I'){
            cin >> b;
            if (b<0){
                cout << "Pogresan parametar. Molimo ponovite unos. " << endl;
                cin.ignore(10000, '\n');
                continue;
            }
            komanda=Komande::Idi;
           IzvrsiKomandu(komanda, b, x, y, orijentacija);
            IspisiPoziciju(x, y, orijentacija);
    }
    if (a=='L'){
            komanda=Komande::Nalijevo;
            IzvrsiKomandu(komanda, b, x, y, orijentacija);
            IspisiPoziciju(x, y, orijentacija);
    }
    if (a=='D'){
        komanda=Komande::Nadesno;
        IzvrsiKomandu(komanda, b, x, y, orijentacija);
        IspisiPoziciju(x, y, orijentacija);
    }
    if (a=='K'){
        komanda=Komande::Kraj;
        IzvrsiKomandu(komanda, b, x, y, orijentacija);

    }
    }
    return 0;
}
