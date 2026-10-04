#include<iostream>
using namespace std;
using ll = long long;


ll pp =17;
ll a=2, b=2; //y^2= x^3+ax+b

struct point{
    ll x,y;
    bool inf = false;
};

ll norm (ll a, ll m){
    return ((a%m)+m)%m;
}

ll modpow(ll a , ll e, ll m){
    ll r=1;
    a%=m;

    while (e){
        if(e&1)
        r=(r*a)%m;
        a=(a*a)%m;
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
    ll g= egcd(b, a%b, x1, y1);
    x=y1;
    y=x1-(a/b)*y1;
    return g;
}

ll modinv(ll a, ll m){
    ll x,y;
    ll g = egcd(a,m,x,y);
    return norm(x,m);
}

ll s;

point add (point p, point q){
    if(p.inf)
    return q;
    if(q.inf)
    return p;

    ll x1=p.x, x2=q.x, y1=p.y, y2=q.y;

    if(x1==x2 && y1==norm(-y2,pp)){
        return {0,0,true};
    }

    if(x1==x2 && y1==y2){
        if(y1==0)
        return {0,0,true};
     s=(3*x1*x1+a)*modinv(norm(2*y1, pp),pp);
    }

    else {
        s=(y2-y1)*modinv(norm(x2-x1,pp),pp);
    }

    s= norm(s,pp);
    ll x3 = norm(s*s - x1 - x2, pp);
    ll y3 = norm(s*(x1 - x3) - y1, pp);

    return {x3, y3};
}
 
point multiply (ll k, point g){
    point r ={0,0,true};
    while(k){
        if(k&1)
        r =add(r,g);
        g=add(g,g);
        k>>=1;
    }
   return r;
}

int main(){
    point g = {5,1};
    ll x =5;
    ll k=3;
    point q= multiply(x,g);

    point m = {6,3};
    point c1 = multiply(k,g);
    point c2 = add(m,multiply(k,q));

    point neg = multiply(x,c1);
    neg.y=norm(-neg.y,pp);

    point dec = add(c2, neg);

cout << "m : " << m.x << " " << m.y << " dec : " << dec.x << " " << dec.y << endl;
    return 0;
}