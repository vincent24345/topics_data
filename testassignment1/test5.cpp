#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Convert character to integer
int charToInt(char ch) {
    return ch - '0';
}

// Convert integer to character representation
char intToChar(int num) {
    return num + '0';
}

// Helper function to normalize string lengths
void normalizeStrings(string &num1, string &num2) {
    while (num1.length() < num2.length()) num1 = "0" + num1;
    while (num2.length() < num1.length()) num2 = "0" + num2;
}

// Efficient addition using vector for carrying
string vectorAddition(string num1, string num2, int base) {
    normalizeStrings(num1, num2);
    vector<int> result(num1.length() + 1, 0); // Extra space for carry
    int carry = 0;

    for (int i = num1.length() - 1; i >= 0; i--) {
        int sum = charToInt(num1[i]) + charToInt(num2[i]) + carry;
        result[i + 1] = sum % base; // Store digit
        carry = sum / base; // Calculate carry
    }
    result[0] = carry; // Store final carry

    // Convert vector back to string
    string resultStr = "";
    for (int digit : result) {
        if (!(resultStr.empty() && digit == 0)) { // Skip leading zero
            resultStr += intToChar(digit);
        }
    }
    return resultStr.empty() ? "0" : resultStr;
}

// Simple multiplication using iterative approach
string simpleMultiplication(string num1, string num2, int base) {
    if (num1 == "0" || num2 == "0") return "0";
    normalizeStrings(num1, num2);
    string result = "0";

    for (int i = num2.length() - 1; i >= 0; i--) {
        int digitMultiplier = charToInt(num2[i]);
        string currentProduct = "";
        int carry = 0;

        // Multiply each digit in num1 by the current digit in num2
        for (int j = num1.length() - 1; j >= 0; j--) {
            int product = charToInt(num1[j]) * digitMultiplier + carry;
            currentProduct = intToChar(product % base) + currentProduct;
            carry = product / base;
        }
        if (carry > 0) currentProduct = intToChar(carry) + currentProduct;

        // Add currentProduct to result
        currentProduct += string(num2.length() - 1 - i, '0'); // Append zeros
        result = vectorAddition(result, currentProduct, base);
    }

    return result;
}

// Function for division of two numbers using long division
string divideNumbers(string num1, string num2, int base) {
    if (num2 == "0") return "Error: Division by zero";
    if (num1 == "0") return "0";

    string result = "";
    string current = "";

    for (char digit : num1) {
        current += digit;
        int count = 0;

        // Keep subtracting num2 from current until current < num2
        while (current.length() > 0 && current[0] == '0') current.erase(current.begin()); // Remove leading zeros
        while (current >= num2) {
            current = vectorAddition(current, "-" + num2, base); // Subtract num2 from current
            count++;
        }
        result += intToChar(count);
    }

    // Trim leading zeros in the result
    while (result.length() > 1 && result[0] == '0') result.erase(result.begin());
    return result.empty() ? "0" : result;
}

int main() {
    string number1, number2;
    int base;
    cin >> number1 >> number2 >> base;
    string additionResult = vectorAddition(number1, number2, base);
    string multiplicationResult = simpleMultiplication(number1, number2, base);
    string divisionResult = divideNumbers(number1, number2, base);
    cout << additionResult << " " << multiplicationResult << " " << divisionResult << endl;
    return 0;
}
