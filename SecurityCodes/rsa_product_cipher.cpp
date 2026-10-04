#include<iostream>
using ll= long long ;
using namespace std;

ll norm(ll a, ll m){
    return ((a%m)+m)%m;
}

ll modpow (ll a, ll e, ll m){
    ll r=1;
    a%=m;
    while(e){
        if(e&1)
        r=(r*a)%m;
        a=(a*a)%m;
        e>>=1;
    }
        return r;
}

ll egcd (ll a, ll b , ll &x, ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }

    ll x1,y1;
    ll g= egcd(b, a%b, x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g;
}


ll modinv(ll a, ll m){
    ll x,y;
    ll g=egcd(a,m,x,y);
    return norm(x,m);
}

int main (){
    ll p=13, q=17,n,phi;
    n=p*q;
    phi=(p-1)*(q-1);
    ll e=2,x,y;
    while(e<phi){
        if(egcd(e,phi,x,y)==1)
        break;
        e++;
    }

    ll d = modinv(e,phi);

    ll a1 = 10, a2 = 5;

    ll c1= modpow(a1,e,n);
    ll c2= modpow(a2,e,n);
    ll c=c1*c2;
    ll dec = modpow (c,d,n);
    cout<<"decrypted : "<<dec<<endl;
    return 0;
}