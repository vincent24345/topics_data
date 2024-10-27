#include <iostream>
#include <string>
using namespace std;

// Function to get the integer value of a character
int getIntFromChar(char c) {
    return c - '0';
}

// Function to convert an integer to its character representation
char getCharFromInt(int number) {
    return number + '0';
}

// Function that adds two base-n numbers
string addBaseNumbers(string num1, string num2, int base) {
    string result = "";
    int carry = 0;

    // Normalize lengths by padding with zeros
    while (num1.length() < num2.length()) num1 = '0' + num1;
    while (num2.length() < num1.length()) num2 = '0' + num2;

    // Perform addition
    for (int i = num1.length() - 1; i >= 0; --i) {
        int sum = getIntFromChar(num1[i]) + getIntFromChar(num2[i]) + carry;
        result = getCharFromInt(sum % base) + result;
        carry = sum / base;
    }

    if (carry > 0) result = getCharFromInt(carry) + result;

    return result;
}

// Function for multiplication of two numbers
string multiplyBaseNumbers(string num1, string num2, int base) {
    int len1 = num1.size();
    int len2 = num2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int product = getIntFromChar(num1[i]) * getIntFromChar(num2[j]) + getIntFromChar(result[i + j + 1]) + carry;
            result[i + j + 1] = getCharFromInt(product % base);
            carry = product / base;
        }
        result[i] = getCharFromInt(getIntFromChar(result[i]) + carry);
    }

    size_t pos = result.find_first_not_of('0');
    return (pos != string::npos) ? result.substr(pos) : "0";
}

// Function to divide two numbers
string divideBaseNumbers(string num1, string num2, int base) {
    return "0"; // Placeholder implementation
}

int main() {
    string numberOne, numberTwo;
    int base;
    cin >> numberOne >> numberTwo >> base;
    cout << addBaseNumbers(numberOne, numberTwo, base) << " "
         << multiplyBaseNumbers(numberOne, numberTwo, base) << " "
         << divideBaseNumbers(numberOne, numberTwo, base) << endl;
    return 0;
}
