#include <iostream>
#include <string>
using namespace std;

int characterToInteger(char ch) {
    return ch - '0';
}

char integerToCharacter(int n) {
    return n + '0';
}

string addStringsBase(string str1, string str2, int base) {
    while (str1.size() < str2.size()) str1 = '0' + str1;
    while (str2.size() < str1.size()) str2 = '0' + str2;

    string result;
    int carry = 0;

    for (int i = str1.size() - 1; i >= 0; i--) {
        int sum = characterToInteger(str1[i]) + characterToInteger(str2[i]) + carry;
        carry = sum / base;
        result = integerToCharacter(sum % base) + result;
    }

    if (carry > 0) result = integerToCharacter(carry) + result;

    return result;
}

string karatsubaBaseMultiply(string str1, string str2, int base) {
    string result(str1.size() + str2.size(), '0');

    for (int i = str1.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = str2.size() - 1; j >= 0; j--) {
            int product = characterToInteger(str1[i]) * characterToInteger(str2[j]) + characterToInteger(result[i + j + 1]) + carry;
            result[i + j + 1] = integerToCharacter(product % base);
            carry = product / base;
        }
        result[i] = integerToCharacter(characterToInteger(result[i]) + carry);
    }

    size_t position = result.find_first_not_of('0');
    return position == string::npos ? "0" : result.substr(position);
}

string baseDivide(string str1, string str2, int base) {
    return "0";
}

int main() {
    string a, b;
    int base;
    cin >> a >> b >> base;

    string sumResult = addStringsBase(a, b, base);
    string productResult = karatsubaBaseMultiply(a, b, base);
    string divideResult = baseDivide(a, b, base);

    cout << sumResult << " " << productResult << " " << divideResult << endl;

    return 0;
}
