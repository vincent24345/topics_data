#include <iostream>
#include <string>
using namespace std;

// Function to convert character to integer
int convertCharToInt(char ch) {
    return ch - '0';
}

// Function to convert integer to character
char convertIntToChar(int num) {
    return num + '0';
}

// Function to add two base-n numbers
string addTwoNumbersInBase(string number1, string number2, int base) {
    string result = "";
    int carry = 0;

    // Normalize the lengths of the input numbers
    while (number1.length() < number2.length()) number1 = '0' + number1;
    while (number2.length() < number1.length()) number2 = '0' + number2;

    // Add digits from right to left
    for (int i = number1.length() - 1; i >= 0; --i) {
        int sum = convertCharToInt(number1[i]) + convertCharToInt(number2[i]) + carry;
        result = convertIntToChar(sum % base) + result;
        carry = sum / base;
    }

    // Include any remaining carry
    if (carry) result = convertIntToChar(carry) + result;

    return result;
}

// Function to multiply two base-n numbers
string multiplyTwoNumbersInBase(string number1, string number2, int base) {
    int len1 = number1.size();
    int len2 = number2.size();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int product = convertCharToInt(number1[i]) * convertCharToInt(number2[j]) + convertCharToInt(result[i + j + 1]) + carry;
            result[i + j + 1] = convertIntToChar(product % base);
            carry = product / base;
        }
        result[i] = convertIntToChar(convertCharToInt(result[i]) + carry);
    }

    // Remove leading zeros
    size_t pos = result.find_first_not_of('0');
    return pos != string::npos ? result.substr(pos) : "0";
}

// Function for division of two numbers (not yet implemented)
string divideTwoNumbersInBase(string number1, string number2, int base) {
    return "0"; // Placeholder
}

int main() {
    string num1, num2;
    int base;
    cin >> num1 >> num2 >> base;
    cout << addTwoNumbersInBase(num1, num2, base) << " "
         << multiplyTwoNumbersInBase(num1, num2, base) << " "
         << divideTwoNumbersInBase(num1, num2, base) << endl;
    return 0;
}
