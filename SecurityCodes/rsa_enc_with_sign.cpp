#include<iostream>

using ll = long long;
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


ll egcd(ll a, ll b, ll &x, ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }

    ll x1,y1;
    ll g= egcd (b, a%b, x1, y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g;
}

ll modinv (ll a, ll m){
    ll x,y;
    ll g= egcd(a,m,x,y);
    return norm(x,m);
}


int main(){
    ll p1=3, q1=11, n1, phi1;
     n1= p1*q1;
     phi1 = (p1-1)*(q1-1);

     ll e1=2,x1,y1;
     while(e1<phi1){
        if(egcd(e1,phi1,x1,y1)==1)
        break;
        e1++;
     }

     ll d1= modinv(e1,phi1);


     ll p2=13, q2=17, n2, phi2;
     n2= p2*q2;
     phi2 = (p2-1)*(q2-1);

     ll e2=2,x2,y2;
     while(e2<phi2){
        if(egcd(e2,phi2,x2,y2)==1)
        break;
        e2++;
     }

     ll d2= modinv(e2,phi2);

     ll m=10;

     cout<<"message :"<<m<<endl;
     ll s= modpow(m,d1,n1);
     cout<<"Signature : " <<s<<endl;
     ll c = modpow(s,e2,n2);
     cout<<"Encrypted : " <<c<<endl;
     ll dec = modpow(c,d2,n2);
     cout<<"Decrypted : " <<dec<<endl;
     ll v=modpow(dec, e1,n1);
     cout<<"Validateion : " <<v<<endl;

    if (v==m)
         cout<<"Valid"<<endl;
    else 
         cout<<"invalid"<<endl;
         
    return 0;     

}