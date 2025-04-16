#include <iostream>
using namespace std;

int rFibNum(int a, int b, int n) {
    if (n == 1)
        return a;
    else if (n == 2)
        return b;
    else
        return rFibNum(a, b, n - 1) + rFibNum(a, b, n - 2);
}

int main() {
    int a, b, n;

    cout << "請輸入前兩項 a 和 b: ";
    cin >> a >> b;

    cout << "請輸入要計算的第 n 項(n ≥ 1):";
    cin >> n;

    if (n < 1) {
        cout << "n 必須 ≥ 1! " << endl;
        return 1;
    }

    cout << "數列前 " << n << " 項為：";
    for (int i = 1; i <= n; i++) {
        cout << rFibNum(a, b, i) << " ";
    }
    cout << endl;

    int result = rFibNum(a, b, n);
    cout << "第 " << n << " 項為：" << result << endl;

    return 0;
}
