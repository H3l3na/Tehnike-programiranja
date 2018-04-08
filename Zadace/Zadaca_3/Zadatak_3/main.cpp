#include <iostream>
#include <set>
#include <stdlib.h>
#include <list>
#include <utility>
#include <iterator>

using namespace std;

enum class Boje {Herc, Karo, Pik, Tref};

list<set<string>> KreirajSpil(){
 list<set<string>> Spil{{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}, {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}, {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}, {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}};
 return Spil;
}

void IzbaciKarte(list<set<string>> &Spil, const pair<int, int> p){
    int a=p.first;
    int b=p.second;

}

int main()
{
    list<set<string>> Spil=KreirajSpil();
    pair<int, int> p={1,2};
    IzbaciKarte(Spil, p);
    cout << endl;
    list<set<string>>::iterator it(Spil.begin());
    for (int i=0; i<3; i++){
        cout << *it++ << " ";
    }
    return 0;
}
