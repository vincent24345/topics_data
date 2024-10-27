#include <iostream>
#include <string>
using namespace std;

int digitToInt(char ch) {
    return ch - '0';
}

char intToDigit(int num) {
    return num + '0';
}

string addNumbers(string num1, string num2, int base) {
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    string result;
    int carry = 0;

    for (int i = num1.length() - 1; i >= 0; --i) {
        int sum = digitToInt(num1[i]) + digitToInt(num2[i]) + carry;
        carry = sum / base;
        result = intToDigit(sum % base) + result;
    }

    if (carry) result = intToDigit(carry) + result;

    return result;
}

string multiplyKaratsuba(string num1, string num2, int base) {
    string result(num1.length() + num2.length(), '0');

    for (int i = num1.length() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = num2.length() - 1; j >= 0; --j) {
            int prod = digitToInt(num1[i]) * digitToInt(num2[j]) + digitToInt(result[i + j + 1]) + carry;
            result[i + j + 1] = intToDigit(prod % base);
            carry = prod / base;
        }
        result[i] = intToDigit(digitToInt(result[i]) + carry);
    }

    size_t pos = result.find_first_not_of('0');
    return pos == string::npos ? "0" : result.substr(pos);
}

string division(string num1, string num2, int base) {
    return "0";
}

int main() {
    string n1, n2;
    int base;
    cin >> n1 >> n2 >> base;

    string sum = addNumbers(n1, n2, base);
    string prod = multiplyKaratsuba(n1, n2, base);
    string div = division(n1, n2, base);

    cout << sum << " " << prod << " " << div << endl;
    return 0;
}
