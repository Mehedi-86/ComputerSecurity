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
    ll p=79, alpha = 6, a=5, beta=modpow(alpha,a,p), m1=12, m2=5, k1=7, k2=9;

   ll c11 = modpow(alpha, k1, p);
   ll c12 = (m1*modpow(beta,k1,p))%p;

   ll c21 = modpow(alpha, k2,p);
   ll c22 = (m2*modpow(beta,k2,p))%p;

    cout<<"m1 : "<<m1<<" m2 : "<<m2<<endl;

   ll c1p= (c11*c21);
   ll c2p = (c12*c22);

   ll dec = (c2p * modinv(modpow(c1p,a,p),p))%p;

   cout<<"m1 * m2 : "<<(m1*m2)<<endl;
   cout<<"decrypted value : "<<dec<<endl;

   if(dec==(m1*m2))
   cout<<"Done"<<endl;
   else cout<<"Not Done"<<endl;

   return 0;
}