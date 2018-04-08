#include <iostream>
#include <string>
#include <vector>

using namespace std;

string IstakniFraze(string s, vector<string> s1){
        int i(0), j(0);
        string s2;
        string s3;
        int k(0), brojac(0);
        while (i<s.size()){
                s3=s1[k];
                while (s[i]!=s3[0] && i<s.size()){
                        s2.push_back(s[i]);
                        i++;
                }
                j=0;
                if (s[i]==s3[j]){
                        int a=i;
                        int b=j;
                        brojac=0;
                        while (s[a]==s3[b] && b<s3.size() && a<s.size()){
                                brojac++;
                                a++;
                                b++;
                        }
                        if (brojac==s3.size()){

                if (s[i]==s3[j] && i<s.size() && j<s3.size()){
                s2+="(";
                        while (s[i]==s3[j] && i<s.size() && j<s3.size()){
                                s2.push_back(s[i]);
                                i++;
                                j++;
                        }
                        s2+=") ";  }
                }}
                if (k<s1.size()-1){
                        k++;
                }
                i++;
        }
        return s2;
}

int main() {
        string s;
        cout << "Unesite string: " << endl;
        getline(cin, s);
        vector<string> v;
        string s1;
        cout << "Unesite broj rijeci: " << endl;
        int n;
        cin >> n;
        cin.ignore(10000, '\n');
        cout << "Unesite rijeci: " << endl;
        for (int i=0; i<n; i++){
                getline(cin, s1);
                v.push_back(s1);
        }
        string s2;
        s2=IstakniFraze(s, v);
        cout << s2;
        return 0;
}
