#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to transform a character into an integer
int characterToInteger(char character) {
    return character - '0';
}

// Function to transform an integer into its character form
char integerToCharacter(int number) {
    return number + '0';
}

// Adding two numbers in a base-n system
string addInBase(string a, string b, int base) {
    string result;
    int carry = 0;

    // Adjust length of strings
    while (a.size() < b.size()) a = '0' + a;
    while (b.size() < a.size()) b = '0' + b;

    // Sum digits from right to left
    for (int i = a.length() - 1; i >= 0; --i) {
        int sum = characterToInteger(a[i]) + characterToInteger(b[i]) + carry;
        result = integerToCharacter(sum % base) + result;
        carry = sum / base;
    }

    if (carry) result = integerToCharacter(carry) + result;

    return result;
}

// Multiplication of two numbers using a long multiplication method
string multiplyInBase(string a, string b, int base) {
    int lenA = a.length();
    int lenB = b.length();
    string result(lenA + lenB, '0');

    for (int i = lenA - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = lenB - 1; j >= 0; --j) {
            int prod = characterToInteger(a[i]) * characterToInteger(b[j]) + characterToInteger(result[i + j + 1]) + carry;
            result[i + j + 1] = integerToCharacter(prod % base);
            carry = prod / base;
        }
        result[i] = integerToCharacter(characterToInteger(result[i]) + carry);
    }

    // Remove leading zeros
    size_t nonZeroPos = result.find_first_not_of('0');
    return nonZeroPos != string::npos ? result.substr(nonZeroPos) : "0";
}

// Function for division (currently not implemented)
string divideInBase(string a, string b, int base) {
    return "0";  // Placeholder
}

int main() {
    string firstNumber, secondNumber;
    int numeralBase;
    cin >> firstNumber >> secondNumber >> numeralBase;
    cout << addInBase(firstNumber, secondNumber, numeralBase) << " "
         << multiplyInBase(firstNumber, secondNumber, numeralBase) << " "
         << divideInBase(firstNumber, secondNumber, numeralBase) << endl;
    return 0;
}
