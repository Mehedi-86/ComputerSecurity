#include <iostream>
#include <string>

using namespace std;

string Enc(string text, int s) {
    // Separate normalized shift values for letters (mod 26) and digits (mod 10)
    int s_alpha = (s % 26 + 26) % 26;
    int s_digit = (s % 10 + 10) % 10;
    
    string enc = "";
    for (char ch : text) {
        if (isupper(ch)) {
            ch = ((ch - 'A' + s_alpha) % 26) + 'A';
        }
        else if (islower(ch)) {
            ch = ((ch - 'a' + s_alpha) % 26) + 'a';
        }
        else if (isdigit(ch)) {
            ch = ((ch - '0' + s_digit) % 10) + '0';
        }
        
        enc += ch;
    }
    return enc;
}

string Dec(string text, int s) {
    return Enc(text, -s);
}

int main() {
    string text;
    int s;

    getline(cin, text);
    cin >> s;

    string encr = Enc(text, s);
    cout << "Encrypted : " << encr << endl;
    cout << "Decrypted : " << Dec(encr, s) << endl;

    return 0;
}