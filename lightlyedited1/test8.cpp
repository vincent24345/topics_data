#include <iostream>
#include <string>
using namespace std;

// Function to convert character to its corresponding integer
int characterToDigit(char character) {
    return character - '0';
}

// Function to convert integer to character
char digitToCharacter(int digit) {
    return digit + '0';
}

// Function for base-n addition of two strings
string addBaseNumbers(string num1, string num2, int base) {
    string result;
    int carry = 0;

    // Make sure both strings are of equal length
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    // Perform addition from least significant digit
    for (int i = num1.length() - 1; i >= 0; --i) {
        int sum = characterToDigit(num1[i]) + characterToDigit(num2[i]) + carry;
        result = digitToCharacter(sum % base) + result;
        carry = sum / base;
    }

    // Append any remaining carry
    if (carry) result = digitToCharacter(carry) + result;

    return result;
}

// Function for base-n multiplication of two strings
string multiplyBaseNumbers(string num1, string num2, int base) {
    int len1 = num1.size();
    int len2 = num2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int product = characterToDigit(num1[i]) * characterToDigit(num2[j]) + characterToDigit(result[i + j + 1]) + carry;
            result[i + j + 1] = digitToCharacter(product % base);
            carry = product / base;
        }
        result[i] = digitToCharacter(characterToDigit(result[i]) + carry);
    }

    // Eliminate leading zeros
    size_t pos = result.find_first_not_of('0');
    return pos != string::npos ? result.substr(pos) : "0";
}

// Placeholder for division
string divideBaseNumbers(string num1, string num2, int base) {
    return "0"; // Placeholder
}

int main() {
    string firstNumber, secondNumber;
    int base;
    cin >> firstNumber >> secondNumber >> base;
    cout << addBaseNumbers(firstNumber, secondNumber, base) << " "
         << multiplyBaseNumbers(firstNumber, secondNumber, base) << " "
         << divideBaseNumbers(firstNumber, secondNumber, base) << endl;
    return 0;
}
