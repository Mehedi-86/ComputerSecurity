#include <iostream>
using ll = long long;
using namespace std;

ll norm (ll a, ll m){
    return ((a%m)+m)%m;
}

ll modpow (ll a, ll e, ll p){
    ll r=1;
    a%=p;
    while(e){
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

ll modinv(ll a, ll m){
    ll x,y;
    ll g = egcd(a,m,x,y);
    return norm(x,m);
}

int main(){
    ll p =79, alpha = 6, a=5, beta = modpow(alpha, a, p), k=2, m=25;


    ll x1,y1;
    while (k<p-1){
        if(egcd(k,p-1,x1,y1)==1)
        break;
        k++;
    }

    ll r = modpow(alpha , k, p);
    ll diff = norm(m-a*r, p-1);
    ll k_inv= modinv(k,p-1);
    ll s= (diff*k_inv)%(p-1);

    ll v1 = modpow(alpha, m, p);
    ll v2 = (modpow(beta,r,p)*modpow(r,s,p))%p;

    if(v1==v2)
    cout<<"verified and valid\n";
    else 
    cout<<"Invalid\n";

    return 0;
}