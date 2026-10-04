#include <iostream>
using ll = long long;
using namespace std;

bool isPrimitive(ll alpha, ll p){
    ll cur =1;
    for(ll k=1; k<p-1; k++){
        cur=(cur*alpha)%p;

        if(cur==1)
        return false;
    }

    cur=(cur*alpha)%p;
    return (cur==1);
}


ll find_primitive(ll p){
    for(ll g =2 ; g<p; g++){
        if(isPrimitive(g,p))
        return g;
        g++;
    }

    return -1;
}


int main (){
    ll p =79;
    ll alpha = find_primitive(p);

    if (alpha==-1)
    cout<<"not found\n";
    else cout<<"Primitive root : "<<alpha<<endl;
    return 0;
}