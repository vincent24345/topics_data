#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//convert a character to its corresponding integer value
int charToNum(char c) {
    return c - '0';
}

//convert an integer back to its character representation
char numToChar(int n) {
    return n + '0';
}

//perform addition using the schoolbook method
string addUsingSchoolMethod(string str1, string str2, int base) {
    string sumResult = "";
    int carry = 0;

    //add leading zeros to make both numbers the same length
    while (str1.length() < str2.length()) str1 = "0" + str1;
    while (str2.length() < str1.length()) str2 = "0" + str2;

    //perform addition from right to left
    for (int i = str1.length() - 1; i >= 0; i--) {
        int sum = charToNum(str1[i]) + charToNum(str2[i]) + carry;
        sumResult = numToChar(sum % base) + sumResult;
        carry = sum / base;
    }

    //handle any remaining carry
    if (carry > 0) sumResult = numToChar(carry) + sumResult;

    return sumResult;
}

//karatsuba multiplication method
string karatsubaMultiply(string str1, string str2, int base) {
    int len1 = str1.size();
    int len2 = str2.size();
    string product(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int prod = charToNum(str1[i]) * charToNum(str2[j]) + charToNum(product[i + j + 1]) + carry;
            product[i + j + 1] = numToChar(prod % base);
            carry = prod / base;
        }
        product[i] = numToChar(charToNum(product[i]) + carry);
    }

    //remove any leading zeros
    size_t pos = product.find_first_not_of('0');
    if (pos != string::npos) return product.substr(pos);
    return "0";
}

//dummy function for division, to be implemented
string divideStrings(string str1, string str2, int base) {
    return "0";
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    string addition = addUsingSchoolMethod(num1, num2, base);
    string multiplication = karatsubaMultiply(num1, num2, base);
    string division = divideStrings(num1, num2, base);
    cout << addition << " " << multiplication << " " << division << endl;
    return 0;
}
