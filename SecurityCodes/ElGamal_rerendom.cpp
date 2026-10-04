#include<iostream>
using ll = long long;
using namespace std;

ll norm (ll a, ll m){
    return ((a%m)+m)%m;
}

ll modpow(ll a, ll e, ll m){
    ll r=1;
    a%=m;

    while(e){
        if(e&1)
        r=(r*a)%m;
        a=(a*a)%m;
        e>>=1;
    }
    return r ;
}

ll egcd (ll a, ll b, ll &x, ll &y){
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
    ll g = egcd(a,m,x,y);
    return norm(x,m);
}

int main (){
    ll p=79, alpha = 6, a=5, beta = modpow(alpha, a ,p), m=25, k1=7,k2=8;
    ll c1 = modpow(alpha , k1, p);
    ll c2 = (m*modpow(beta, k1, p))%p;

    ll c1p = (c1*modpow(alpha,k2,p))%p;
    ll c2p = (c2*modpow(beta, k2, p))%p;

    ll dec = (c2p*modinv(modpow(c1p, a, p),p))%p;

    cout <<"m : "<<m<<" Decrypted value : "<<dec<<endl;

    return 0;
}