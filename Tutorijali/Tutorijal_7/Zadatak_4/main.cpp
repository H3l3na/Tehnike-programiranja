#include <iostream>
#include <stdexcept>
#include <new>
#include <set>
#include <algorithm>

using namespace std;

template <typename tip>

set<tip> Presjek(set<tip> s1, set<tip> s2){
    set<tip> s3;
    for (auto i=s1.begin(); i!=s1.end(); i++){
        if (count(s2.begin(), s2.end(), *i)){
            s3.insert(*i);
        }
    }
    return s3;
}

template <typename tip>

set<tip> Unija(set<tip> s1, set<tip> s2){
    for (auto i=s2.begin(); i!=s2.end(); i++){
        s1.insert(*i);
    }
   /* for (auto i=s1.begin(); i!=s1.end(); i++){
        s3.insert(*i);
    }
    for (auto i=s2.begin(); i!=s2.end(); i++){
        s3.insert(*i);
    }*/
    return s1;
}

int main()
{
    set<int> s1{1,2,3,4,5}, s2{2,3, 4, 7, 8};
    set<int> s3;
    s3=Presjek(s1, s2);
    cout << "Presjek: " << endl;
    for (auto i: s3){
            cout << i << endl;
    }
    set<int> s4=Unija(s1, s2);
    cout << "Unija: " << endl;
    for (auto i: s4){
        cout << i << endl;
    }
    return 0;
}
