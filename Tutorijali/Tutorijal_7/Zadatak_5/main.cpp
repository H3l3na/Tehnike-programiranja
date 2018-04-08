#include <iostream>
#include <new>
#include <algorithm>
#include <string.h>
#include <iterator>

using namespace std;

string IzvrniString(string s){
    string pomocni;
    remove_copy(s.rbegin(), s.rend(), back_inserter(pomocni), ' ');
    return pomocni;
}

int main()
{
    string s="Evo pada kisa";
    string rez=IzvrniString(s);
    cout << rez;
    return 0;
}
