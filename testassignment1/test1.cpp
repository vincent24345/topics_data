#include <iostream>
#include <string>
using namespace std;

int convertCharToInt(char c) {
    return c - '0';
}

char convertIntToChar(int n) {
    return n + '0';
}

string addNumbers(string a, string b, int base) {
    string result = "";
    int carry = 0;

    while (a.length() < b.length()) a = "0" + a;
    while (b.length() < a.length()) b = "0" + b;

    for (int i = a.length() - 1; i >= 0; i--) {
        int sum = convertCharToInt(a[i]) + convertCharToInt(b[i]) + carry;
        result = convertIntToChar(sum % base) + result;
        carry = sum / base;
    }

    if (carry) result = convertIntToChar(carry) + result;

    return result;
}

string karatsubaMultiply(string a, string b, int base) {
    int lenA = a.size(), lenB = b.size();
    string res(lenA + lenB, '0');

    for (int i = lenA - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = lenB - 1; j >= 0; j--) {
            int prod = convertCharToInt(a[i]) * convertCharToInt(b[j]) + convertCharToInt(res[i + j + 1]) + carry;
            res[i + j + 1] = convertIntToChar(prod % base);
            carry = prod / base;
        }
        res[i] = convertIntToChar(convertCharToInt(res[i]) + carry);
    }

    size_t pos = res.find_first_not_of('0');
    return pos != string::npos ? res.substr(pos) : "0";
}

string divide(string a, string b, int base) {
    return "0";
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;

    string sum = addNumbers(num1, num2, base);
    string product = karatsubaMultiply(num1, num2, base);
    string quotient = divide(num1, num2, base);

    cout << sum << " " << product << " " << quotient << endl;
    return 0;
}
