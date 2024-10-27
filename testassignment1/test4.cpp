#include <iostream>
#include <string>
using namespace std;

int charToDigit(char c) {
    return c - '0';
}

char digitToChar(int d) {
    return d + '0';
}

string addLargeNumbers(string x, string y, int base) {
    while (x.length() < y.length()) x = '0' + x;
    while (y.length() < x.length()) y = '0' + y;

    string result = "";
    int carry = 0;

    for (int i = x.length() - 1; i >= 0; i--) {
        int sum = charToDigit(x[i]) + charToDigit(y[i]) + carry;
        carry = sum / base;
        result = digitToChar(sum % base) + result;
    }

    if (carry) result = digitToChar(carry) + result;

    return result;
}

string karatsubaMultiply(string a, string b, int base) {
    string result(a.size() + b.size(), '0');

    for (int i = a.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = b.size() - 1; j >= 0; --j) {
            int prod = charToDigit(a[i]) * charToDigit(b[j]) + charToDigit(result[i + j + 1]) + carry;
            result[i + j + 1] = digitToChar(prod % base);
            carry = prod / base;
        }
        result[i] = digitToChar(charToDigit(result[i]) + carry);
    }

    size_t pos = result.find_first_not_of('0');
    return pos == string::npos ? "0" : result.substr(pos);
}

string divideLargeNumbers(string a, string b, int base) {
    return "0";
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;

    string addition = addLargeNumbers(num1, num2, base);
    string multiplication = karatsubaMultiply(num1, num2, base);
    string division = divideLargeNumbers(num1, num2, base);

    cout << addition << " " << multiplication << " " << division << endl;

    return 0;
}
