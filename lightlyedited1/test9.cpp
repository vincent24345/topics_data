#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to convert character to integer
int charToIntValue(char character) {
    return character - '0';
}

// Function to convert integer to character
char intValueToChar(int value) {
    return value + '0';
}

// Function to perform addition of two numbers in a given base
string addInBase(string firstNumber, string secondNumber, int base) {
    string result;
    int carry = 0;

    // Equalize the length of the two numbers
    while (firstNumber.length() < secondNumber.length()) firstNumber = '0' + firstNumber;
    while (secondNumber.length() < firstNumber.length()) secondNumber = '0' + secondNumber;

    // Add the numbers digit by digit
    for (int i = firstNumber.length() - 1; i >= 0; --i) {
        int sum = charToIntValue(firstNumber[i]) + charToIntValue(secondNumber[i]) + carry;
        result = intValueToChar(sum % base) + result;
        carry = sum / base;
    }

    // Add remaining carry if necessary
    if (carry) result = intValueToChar(carry) + result;

    return result;
}

// Function for multiplication of two numbers in base-n
string multiplyInBase(string firstNumber, string secondNumber, int base) {
    int len1 = firstNumber.size();
    int len2 = secondNumber.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int product = charToIntValue(firstNumber[i]) * charToIntValue(secondNumber[j]) + charToIntValue(result[i + j + 1]) + carry;
            result[i + j + 1] = intValueToChar(product % base);
            carry = product / base;
        }
        result[i] = intValueToChar(charToIntValue(result[i]) + carry);
    }

    // Remove leading zeros
    size_t pos = result.find_first_not_of('0');
    return pos != string::npos ? result.substr(pos) : "0";
}

// Division of two numbers (not implemented)
string divideInBase(string firstNumber, string secondNumber, int base) {
    return "0"; // Placeholder
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    cout << addInBase(num1, num2, base) << " "
         << multiplyInBase(num1, num2, base) << " "
         << divideInBase(num1, num2, base) << endl;
    return 0;
}
