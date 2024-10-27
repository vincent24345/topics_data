#include <iostream>
#include <string>
using namespace std;

int toInt(char c) {
    return c - '0';
}

char toChar(int n) {
    return n + '0';
}

string addStrings(string a, string b, int base) {
    int carry = 0;
    string sum = "";

    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    for (int i = a.size() - 1; i >= 0; i--) {
        int s = toInt(a[i]) + toInt(b[i]) + carry;
        carry = s / base;
        sum = toChar(s % base) + sum;
    }

    if (carry > 0) sum = toChar(carry) + sum;

    return sum;
}

string multiply(string a, string b, int base) {
    int len1 = a.length(), len2 = b.length();
    string res(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int product = toInt(a[i]) * toInt(b[j]) + toInt(res[i + j + 1]) + carry;
            res[i + j + 1] = toChar(product % base);
            carry = product / base;
        }
        res[i] = toChar(toInt(res[i]) + carry);
    }

    size_t pos = res.find_first_not_of('0');
    return pos != string::npos ? res.substr(pos) : "0";
}

string divideNums(string a, string b, int base) {
    return "0";
}

int main() {
    string n1, n2;
    int base;
    cin >> n1 >> n2 >> base;

    string sumResult = addStrings(n1, n2, base);
    string multiplyResult = multiply(n1, n2, base);
    string divideResult = divideNums(n1, n2, base);

    cout << sumResult << " " << multiplyResult << " " << divideResult << endl;

    return 0;
}
