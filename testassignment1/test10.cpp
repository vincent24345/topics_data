#include <iostream>
#include <string>
using namespace std;

int ctoi(char c) {
    return c - '0';
}

char itoc(int n) {
    return n + '0';
}

string addNumStrings(string a, string b, int base) {
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    string result = "";
    int carry = 0;

    for (int i = a.length() - 1; i >= 0; i--) {
        int sum = ctoi(a[i]) + ctoi(b[i]) + carry;
        carry = sum / base;
        result = itoc(sum % base) + result;
    }

    if (carry) result = itoc(carry) + result;

    return result;
}

string multiplyNumStrings(string a, string b, int base) {
    string result(a.size() + b.size(), '0');

    for (int i = a.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = b.size() - 1; j >= 0; --j) {
            int prod = ctoi(a[i]) * ctoi(b[j]) + ctoi(result[i + j + 1]) + carry;
            result[i + j + 1] = itoc(prod % base);
            carry = prod / base;
        }
        result[i] = itoc(ctoi(result[i]) + carry);
    }

    size_t pos = result.find_first_not_of('0');
    return pos != string::npos ? result.substr(pos) : "0";
}

string divideNumStrings(string a, string b, int base) {
    return "0";
}

int main() {
    string x, y;
    int base;
    cin >> x >> y >> base;

    string sumResult = addNumStrings(x, y, base);
    string productResult = multiplyNumStrings(x, y, base);
    string divideResult = divideNumStrings(x, y, base);

    cout << sumResult << " " << productResult << " " << divideResult << endl;

    return 0;
}
