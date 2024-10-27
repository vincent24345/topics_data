#include <iostream>
#include <string>
using namespace std;

// Convert a character to its integer value
int charToValue(char c) {
    return c - '0';
}

// Convert an integer to its character equivalent
char valueToChar(int value) {
    return value + '0';
}

// Perform addition of two numbers in a given base
string addTwoNumbers(string num1, string num2, int base) {
    string result;
    int carry = 0;

    // Pad with zeros to make them the same length
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    // Add from the last digit to the first
    for (int i = num1.length() - 1; i >= 0; --i) {
        int total = charToValue(num1[i]) + charToValue(num2[i]) + carry;
        result = valueToChar(total % base) + result;
        carry = total / base;
    }

    // Handle remaining carry
    if (carry) result = valueToChar(carry) + result;

    return result;
}

// Perform multiplication of two numbers
string multiplyTwoNumbers(string num1, string num2, int base) {
    int len1 = num1.size();
    int len2 = num2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int prod = charToValue(num1[i]) * charToValue(num2[j]) + charToValue(result[i + j + 1]) + carry;
            result[i + j + 1] = valueToChar(prod % base);
            carry = prod / base;
        }
        result[i] = valueToChar(charToValue(result[i]) + carry);
    }

    // Remove leading zeros
    size_t nonZeroIndex = result.find_first_not_of('0');
    return nonZeroIndex != string::npos ? result.substr(nonZeroIndex) : "0";
}

// Division of two numbers (not yet implemented)
string divideTwoNumbers(string num1, string num2, int base) {
    return "0"; // Placeholder
}

int main() {
    string firstNum, secondNum;
    int base;
    cin >> firstNum >> secondNum >> base;
    cout << addTwoNumbers(firstNum, secondNum, base) << " "
         << multiplyTwoNumbers(firstNum, secondNum, base) << " "
         << divideTwoNumbers(firstNum, secondNum, base) << endl;
    return 0;
}
