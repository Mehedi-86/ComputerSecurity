#include <iostream>
using namespace std;
using ll = long long;

ll pp = 17;
ll a = 2, b = 2; // y^2 = x^3 + 2x + 2 (mod 17)

struct point {
    ll x, y;
    bool inf = false;
};

ll norm(ll a, ll m) {
    return ((a % m) + m) % m;
}

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll modinv(ll a, ll m) {
    ll x, y;
    egcd(a, m, x, y);
    return norm(x, m);
}

point add(point p, point q) {
    if (p.inf) return q;
    if (q.inf) return p;

    ll x1 = p.x, x2 = q.x, y1 = p.y, y2 = q.y;

    if (x1 == x2 && y1 == norm(-y2, pp))
        return {0, 0, true};

    ll s;
    if (x1 == x2 && y1 == y2) {
        if (y1 == 0) return {0, 0, true};
        s = (3 * x1 * x1 + a) * modinv(norm(2 * y1, pp), pp);
    } else {
        s = (y2 - y1) * modinv(norm(x2 - x1, pp), pp);
    }
    s = norm(s, pp);

    ll x3 = norm(s * s - x1 - x2, pp);
    ll y3 = norm(s * (x1 - x3) - y1, pp);
    return {x3, y3};
}

point multiply(ll k, point g) {
    point r = {0, 0, true};
    while (k) {
        if (k & 1) r = add(r, g);
        g = add(g, g);
        k >>= 1;
    }
    return r;
}

int main() {
    point g = {5, 1};

    
    ll x = 5;                  
    point q = multiply(x, g);  

    point m1 = {6, 3};
    point m2 = {3, 1};

   
    ll k1 = 2;
    point c1_a = multiply(k1, g);
    point c2_a = add(m1, multiply(k1, q));

    
    ll k2 = 3;
    point c1_b = multiply(k2, g);
    point c2_b = add(m2, multiply(k2, q));

   
    point c1_sum = add(c1_a, c1_b);
    point c2_sum = add(c2_a, c2_b);

    // Decrypt the combined ciphertext
    point neg = multiply(x, c1_sum);
    neg.y = norm(-neg.y, pp);
    point dec_sum = add(c2_sum, neg);

   
    point expected = add(m1, m2);

    cout << "Expected (m1 + m2): " << expected.x << " " << expected.y << endl;
    cout << "Decrypted sum     : " << dec_sum.x << " " << dec_sum.y << endl;

    if (dec_sum.x == expected.x && dec_sum.y == expected.y)
        cout << "Additive Homomorphism Verified!" << endl;
    else
        cout << "Failed!" << endl;

    return 0;
}