#include <iostream>
#include <new>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <string.h>

using namespace std;

bool FunKriterija(char s1[], char s2[]){
    return (strcmp(s1, s2)<0);
}

int main()
{
    cout << "Unesite broj recenica: " << endl;
    int n;
    cin >> n;
    cin.ignore(10000, '\n');
    char **recenice{nullptr};
    cout << "Unesite recenice: " << endl;
    try{
        recenice=new char*[n];
        for (int i=0; i<n; i++){
            char radni_prostor[1000];
            cin.getline(radni_prostor, sizeof radni_prostor);
            recenice[i]=new char[strlen(radni_prostor)+1];
            strcpy(recenice[i], radni_prostor);

        }
        for (int i=0; i<n; i++){
            for (int j=i+1; j<n; j++){
                if (strcmp(recenice[i], recenice[j])>0){
                    char temp[100];
                    strcpy(temp, recenice[i]);
                    strcpy(recenice[i], recenice[j]);
                    strcpy(recenice[j], temp);
                }
            }
        }
        for (int i=0; i<n; i++){
            cout << recenice[i] << endl;
        }

    }catch(...){
        for (int i=0; i<n; i++){
            delete [] recenice[i];
        }
        delete [] recenice;
    }

    return 0;
}
