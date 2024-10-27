#include <iostream>
#include <string>
using namespace std;

int convertChar(char c) {
    return c - '0';
}

char convertToChar(int n) {
    return n + '0';
}

string sumStrings(string num1, string num2, int base) {
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    string result = "";
    int carry = 0;

    for (int i = num1.length() - 1; i >= 0; i--) {
        int sum = convertChar(num1[i]) + convertChar(num2[i]) + carry;
        carry = sum / base;
        result = convertToChar(sum % base) + result;
    }

    if (carry) result = convertToChar(carry) + result;

    return result;
}

string karatsubaMulti(string num1, string num2, int base) {
    string result(num1.size() + num2.size(), '0');

    for (int i = num1.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; --j) {
            int product = convertChar(num1[i]) * convertChar(num2[j]) + convertChar(result[i + j + 1]) + carry;
            result[i + j + 1] = convertToChar(product % base);
            carry = product / base;
        }
        result[i] = convertToChar(convertChar(result[i]) + carry);
    }

    size_t pos = result.find_first_not_of('0');
    return pos != string::npos ? result.substr(pos) : "0";
}

string divideFunction(string num1, string num2, int base) {
    return "0";
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;

    string sum = sumStrings(num1, num2, base);
    string product = karatsubaMulti(num1, num2, base);
    string division = divideFunction(num1, num2, base);

    cout << sum << " " << product << " " << division << endl;
    return 0;
}
