#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Convert character to integer
int charToInt(char ch) {
    return ch - '0';
}

// Convert integer to character representation
char intToChar(int num) {
    return num + '0';
}

// School method for addition in a given base
string schoolAddition(string num1, string num2, int base) {
    string result = "";
    int carryOver = 0;

    // Pad with leading zeros to make both numbers of equal length
    while (num1.length() < num2.length()) num1 = "0" + num1;
    while (num2.length() < num1.length()) num2 = "0" + num2;

    // Addition from right to left
    for (int i = num1.length() - 1; i >= 0; --i) {
        int sum = charToInt(num1[i]) + charToInt(num2[i]) + carryOver;
        result = intToChar(sum % base) + result;
        carryOver = sum / base;
    }

    // Handle final carry over
    if (carryOver > 0) result = intToChar(carryOver) + result;

    return result;
}

// Function for Karatsuba multiplication (long multiplication method here)
string karatsubaMultiplication(string num1, string num2, int base) {
    int length1 = num1.size();
    int length2 = num2.size();
    string result(length1 + length2, '0');

    for (int i = length1 - 1; i >= 0; --i) {
        int carryOver = 0;
        for (int j = length2 - 1; j >= 0; --j) {
            int product = charToInt(num1[i]) * charToInt(num2[j]) + charToInt(result[i + j + 1]) + carryOver;
            result[i + j + 1] = intToChar(product % base);
            carryOver = product / base;
        }
        result[i] = intToChar(charToInt(result[i]) + carryOver);
    }

    // Remove leading zeros
    size_t position = result.find_first_not_of('0');
    if (position != string::npos) return result.substr(position);
    return "0";
}

// Function for division of two numbers (not implemented)
string divideNumbers(string num1, string num2, int base) {
    // Placeholder function for division
    return "0";
}

int main() {
    string number1, number2;
    int base;

    // Input the two numbers and the base
    cin >> number1 >> number2 >> base;

    // Perform addition, multiplication, and division
    string additionResult = schoolAddition(number1, number2, base);
    string multiplicationResult = karatsubaMultiplication(number1, number2, base);
    string divisionResult = divideNumbers(number1, number2, base);

    // Output the results
    cout << additionResult << " " << multiplicationResult << " " << divisionResult << endl;

    return 0;
}
