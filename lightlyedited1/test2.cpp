#include <iostream>
#include <string>
using namespace std;

// Helper to convert a character digit to its integer value
int convertCharToInt(char c) {
    return c - '0';
}

// Helper to convert an integer value to its character representation
char convertIntToChar(int num) {
    return num + '0';
}

// Function to perform addition using the school method
string performAddition(string firstNum, string secondNum, int numeralBase) {
    string sumResult = "";
    int carry = 0;

    // Equalize the lengths of both numbers
    while (firstNum.length() < secondNum.length()) firstNum = "0" + firstNum;
    while (secondNum.length() < firstNum.length()) secondNum = "0" + secondNum;

    // Perform addition from right to left
    for (int index = firstNum.length() - 1; index >= 0; --index) {
        int total = convertCharToInt(firstNum[index]) + convertCharToInt(secondNum[index]) + carry;
        sumResult = convertIntToChar(total % numeralBase) + sumResult;
        carry = total / numeralBase;
    }

    // Append carry if present
    if (carry > 0) sumResult = convertIntToChar(carry) + sumResult;

    return sumResult;
}

// Function to perform multiplication using Karatsuba's method
string performMultiplication(string firstNum, string secondNum, int numeralBase) {
    int len1 = firstNum.size();
    int len2 = secondNum.size();
    string productResult(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int prod = convertCharToInt(firstNum[i]) * convertCharToInt(secondNum[j]) + convertCharToInt(productResult[i + j + 1]) + carry;
            productResult[i + j + 1] = convertIntToChar(prod % numeralBase);
            carry = prod / numeralBase;
        }
        productResult[i] = convertIntToChar(convertCharToInt(productResult[i]) + carry);
    }

    // Remove leading zeros
    size_t firstNonZero = productResult.find_first_not_of('0');
    return (firstNonZero != string::npos) ? productResult.substr(firstNonZero) : "0";
}

// Placeholder function for division (to be implemented)
string performDivision(string firstNum, string secondNum, int numeralBase) {
    return "0";  // Placeholder implementation
}

int main() {
    string num1, num2;
    int baseValue;
    cin >> num1 >> num2 >> baseValue;
    cout << performAddition(num1, num2, baseValue) << " "
         << performMultiplication(num1, num2, baseValue) << " "
         << performDivision(num1, num2, baseValue) << endl;
    return 0;
}
