#include <iostream>
#include <functional>

using namespace std;

function <int(int)> IteriranaFunkcija (function <int(int)> f, int n){
    function <int(int)> fun(f);
    for (int i=0; i<n-1; i++){
        fun=[fun,f] (int n){
            return fun(f(n));
        };
    }
    return fun;
}


int main()
{
    auto f=[] (int arg){ return (arg*2);};
    auto g=IteriranaFunkcija(f, 2);
    cout << g(2);
    return 0;
}
