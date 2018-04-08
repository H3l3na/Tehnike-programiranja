#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef std::map<std::string, std::string> Rjecnik;

std::string ZamijeniPremaRjecniku(const string &s, const Rjecnik &r){
    std::string p;
    int pocetni_indeks=0;
    for (int i=0; i<s.size(); i++){
        if (s[i]==' '){
            std::string rijec=s.substr(pocetni_indeks, i-pocetni_indeks);

        if (r.count(rijec)==1){
            p+=r.find(rijec)->second+' ';
        }else{
            p+=rijec+' ';
        }
        pocetni_indeks=i+1;
        }
    }
    std::string rijec=s.substr(pocetni_indeks, s.size()-pocetni_indeks);
    if (r.count(rijec)==1){
        p+=r.find(rijec)->second;
    }
    else{
        p+=rijec;
    }
    return p;


}

int main()
{
    Rjecnik moj_rjecnik={{"kako", "how"}, {"ne", "no"}, {"da", "yes"}};
    cout << ZamijeniPremaRjecniku("kako da ne", moj_rjecnik);
    return 0;
}
