#include<iostream>
using ll=long long;
using namespace std;

ll norm (ll a, ll m){
    return ((a%m)+m)%m;
}

ll modpow(ll a, ll e, ll p){
    ll r=1;
    a%=p;

    while (e){
        if(e&1)
        r=(r*a)%p;
        a=(a*a)%p;
        e>>=1;
    }
    return r;
}

ll egcd (ll a, ll b, ll &x, ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }

    ll x1,y1;
    ll g= egcd (b, a%b, x1,y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g;
}

ll modinv (ll a , ll m){
    ll x,y;
    ll g=egcd(a,m,x,y);
    return norm(x,m);
}


int main (){
    ll p=79, alpha = 6, a=5, beta = modpow(alpha, a, p), k=7, m=25;

    ll c1 = modpow(alpha, k, p);
    ll c2 = m*modpow(beta,k,p)%p;


    cout <<"cipher1 : "<<c1<<"\ncipher2 : "<<c2<<"\n";

    ll dec = c2*modinv(modpow(c1,a,p),p)%p;

    cout<< "decrypted : "<<dec<<endl;

    if (dec==m)
    cout<<"valid"<<endl;
    else 
    cout<<"Invalid"<<endl;

    return 0;
}