#include <iostream>
#include <string>
using namespace std;

// Converts a character to its corresponding integer
int charToInteger(char c) {
    return c - '0';
}

// Converts an integer to its corresponding character
char integerToChar(int number) {
    return number + '0';
}

// Adds two numbers in a specified base
string addStrings(string first, string second, int base) {
    string result = "";
    int carry = 0;

    // Pad shorter string with zeros
    while (first.length() < second.length()) first = '0' + first;
    while (second.length() < first.length()) second = '0' + second;

    // Add each digit from right to left
    for (int i = first.size() - 1; i >= 0; --i) {
        int total = charToInteger(first[i]) + charToInteger(second[i]) + carry;
        result = integerToChar(total % base) + result;
        carry = total / base;
    }

    // Include final carry if exists
    if (carry) result = integerToChar(carry) + result;

    return result;
}

// Multiplies two numbers using the long multiplication method
string multiplyStrings(string first, string second, int base) {
    int len1 = first.size();
    int len2 = second.size();
    string product(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int currentProduct = charToInteger(first[i]) * charToInteger(second[j]) + charToInteger(product[i + j + 1]) + carry;
            product[i + j + 1] = integerToChar(currentProduct % base);
            carry = currentProduct / base;
        }
        product[i] = integerToChar(charToInteger(product[i]) + carry);
    }

    // Remove leading zeros
    size_t firstNonZero = product.find_first_not_of('0');
    return firstNonZero != string::npos ? product.substr(firstNonZero) : "0";
}

// Function to handle division (to be defined)
string divideStrings(string first, string second, int base) {
    return "0"; // Placeholder
}

int main() {
    string input1, input2;
    int baseValue;
    cin >> input1 >> input2 >> baseValue;
    cout << addStrings(input1, input2, baseValue) << " "
         << multiplyStrings(input1, input2, baseValue) << " "
         << divideStrings(input1, input2, baseValue) << endl;
    return 0;
}
