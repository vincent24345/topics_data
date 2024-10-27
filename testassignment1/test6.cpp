#include <iostream>
#include <string>
using namespace std;

int charToNum(char ch) {
    return ch - '0';
}

char numToChar(int num) {
    return num + '0';
}

string addBaseN(string num1, string num2, int base) {
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    string result = "";
    int carry = 0;

    for (int i = num1.length() - 1; i >= 0; --i) {
        int sum = charToNum(num1[i]) + charToNum(num2[i]) + carry;
        carry = sum / base;
        result = numToChar(sum % base) + result;
    }

    if (carry) result = numToChar(carry) + result;

    return result;
}

string karatsubaMultiplyBaseN(string num1, string num2, int base) {
    string result(num1.size() + num2.size(), '0');

    for (int i = num1.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; j >= 0; --j) {
            int product = charToNum(num1[i]) * charToNum(num2[j]) + charToNum(result[i + j + 1]) + carry;
            result[i + j + 1] = numToChar(product % base);
            carry = product / base;
        }
        result[i] = numToChar(charToNum(result[i]) + carry);
    }

    size_t pos = result.find_first_not_of('0');
    return pos != string::npos ? result.substr(pos) : "0";
}

string divideNumbersBaseN(string num1, string num2, int base) {
    return "0";
}

int main() {
    string n1, n2;
    int base;
    cin >> n1 >> n2 >> base;

    string sum = addBaseN(n1, n2, base);
    string product = karatsubaMultiplyBaseN(n1, n2, base);
    string div = divideNumbersBaseN(n1, n2, base);

    cout << sum << " " << product << " " << div << endl;
    return 0;
}
