#include <iostream>
#include <string>
using namespace std;

int toInteger(char c) {
    return c - '0';
}

char toChar(int n) {
    return n + '0';
}

string add(string x, string y, int base) {
    while (x.length() < y.length()) x = '0' + x;
    while (y.length() < x.length()) y = '0' + y;

    string res = "";
    int carry = 0;

    for (int i = x.length() - 1; i >= 0; i--) {
        int sum = toInteger(x[i]) + toInteger(y[i]) + carry;
        carry = sum / base;
        res = toChar(sum % base) + res;
    }

    if (carry) res = toChar(carry) + res;

    return res;
}

string multiply(string x, string y, int base) {
    string res(x.size() + y.size(), '0');

    for (int i = x.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = y.size() - 1; j >= 0; --j) {
            int prod = toInteger(x[i]) * toInteger(y[j]) + toInteger(res[i + j + 1]) + carry;
            res[i + j + 1] = toChar(prod % base);
            carry = prod / base;
        }
        res[i] = toChar(toInteger(res[i]) + carry);
    }

    size_t pos = res.find_first_not_of('0');
    return pos != string::npos ? res.substr(pos) : "0";
}

string divide(string x, string y, int base) {
    return "0";
}

int main() {
    string a, b;
    int base;
    cin >> a >> b >> base;

    string sumResult = add(a, b, base);
    string multiplyResult = multiply(a, b, base);
    string divideResult = divide(a, b, base);

    cout << sumResult << " " << multiplyResult << " " << divideResult << endl;
    return 0;
}
