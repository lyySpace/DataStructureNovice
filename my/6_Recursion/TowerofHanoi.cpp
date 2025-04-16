#include <iostream>
using namespace std;

int moveCount = 0;

void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << from << " to " << to << endl;
        moveCount++;
    }
    else {
        hanoi(n-1, from, aux, to);              // 先把 n-1 移到 aux
        cout << from << " to " << to << endl;
        moveCount++;
        hanoi(n-1, aux, to, from);              // 再把 n-1 從 aux 移到 to
    }
}

int main() {
    int n;
    cout << "請輸入圓盤數：";
    cin >> n;

    cout << "\n移動步驟如下: " << endl;
    hanoi(n, '1', '2', '3'); 

    cout << "\n總共移動了 " << moveCount << " 步" << endl;

    return 0;
}
