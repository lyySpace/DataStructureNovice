#include <iostream>
#include <string>
using namespace std;

// 前半段1的數量和後半段1的數量相同
void generateBinary(int n, string current, int leftSum, int rightSum, int index) {
    // base case
    if (index == n) {
        cout << current;
        if (leftSum == rightSum)
            cout << " Y";
        cout << endl;
        return;
    }

    int half = n / 2;

    // 加上 '0'
    if (index < half)
        generateBinary(n, current + "0", leftSum, rightSum, index + 1);
    else
        generateBinary(n, current + "0", leftSum, rightSum, index + 1);

    // 加上 '1'
    if (index < half)
        generateBinary(n, current + "1", leftSum + 1, rightSum, index + 1);
    else
        generateBinary(n, current + "1", leftSum, rightSum + 1, index + 1);
}

int main() {
    int N;
    cout << "請輸入偶數 N:";
    cin >> N;

    if (N % 2 != 0) {
        cout << "N 必須是偶數！" << endl;
        return 0;
    }

    generateBinary(N, "", 0, 0, 0);
    return 0;
}
