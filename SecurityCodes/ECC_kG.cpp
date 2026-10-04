#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

ll pp = 17;
ll a = 2, b = 2; // Curve: y^2 = x^3 + 2x + 2 (mod 17)

struct point {
    ll x, y;
    bool inf = false;
};

ll norm(ll a, ll m) {
    return ((a % m) + m) % m;
}

ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
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

// Point Addition (P + Q)
point add(point p, point q) {
    if (p.inf) return q;
    if (q.inf) return p;

    ll x1 = p.x, x2 = q.x, y1 = p.y, y2 = q.y;

    if (x1 == x2 && y1 == norm(-y2, pp)) {
        return {0, 0, true};
    }

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
        if (k & 1)
            r = add(r, g);
        g = add(g, g);
        k >>= 1;
    }
    return r;
}

void printPoint(const string& label, point p) {
    if (p.inf) {
        cout << label << " = Point at Infinity\n";
    } else {
        cout << label << " = (" << p.x << ", " << p.y << ")\n";
    }
}

void compute_kG(ll k, point g) {
    if (k <= 0) {
        printPoint("Result (0G)", {0, 0, true});
        return;
    }

    cout << " Computing " << k << "G step-by-step\n";

    cout << "[Phase 1: Doubling using multiply(2, ...)]\n";

    vector<pair<ll, point>> powers;
    point cur = g;
    ll multiplier = 1;

    powers.push_back({multiplier, cur});
    printPoint("Base point: 1G", cur);

    while (multiplier * 2 <= k) {
        cur = multiply(2, cur); // doubling via multiply
        multiplier *= 2;
        powers.push_back({multiplier, cur});
        printPoint("Doubling:   " + to_string(multiplier) + "G = 2 * " + to_string(multiplier / 2) + "G", cur);
    }

    cout << "\n[Phase 2: Addition using add(...)]\n";

    point result = {0, 0, true};
    ll accumulated_k = 0;
    bool is_first = true;

    for (const auto& entry : powers) {
        ll power = entry.first;
        point pt = entry.second;

        if (k & power) { 
            if (is_first) {
                result = pt;
                accumulated_k = power;
                printPoint("Start with: " + to_string(accumulated_k) + "G", result);
                is_first = false;
            } else {
                result = add(result, pt); 
                accumulated_k += power;
                printPoint("Adding:     " + to_string(accumulated_k) + "G = " +
                           to_string(accumulated_k - power) + "G + " + to_string(power) + "G", result);
            }
        }
    }

  
    printPoint("Final Target " + to_string(k) + "G", result);
    
}

int main() {
    point g = {5, 1}; // Generator base point
    ll k;

    cout << "Enter scalar k: ";
    if (cin >> k) {
        compute_kG(k, g);
    }

    return 0;
}