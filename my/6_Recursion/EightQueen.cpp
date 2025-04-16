#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int N = 8;
vector<int> queen(N); // queen[i] = column 放在第 i 列的第幾欄
int totalSolutions = 0;

bool isSafe(int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (queen[i] == col || abs(queen[i] - col) == abs(i - row)) // 斜率絕對值為1
            return false; // 同欄 或 對角線衝突
    }
    return true;
}

void solve(int row) {
    if (row == N) {
        totalSolutions++;
        // 印出其中一個解
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (queen[i] == j)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
        cout << "---------------------" << endl;
        return;
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(row, col)) {
            queen[row] = col;     // 做選擇
            solve(row + 1);       // 遞迴往下一列
            // 回溯時會覆蓋 queen[row]，所以不需要特別撤銷
        }
    }
}

int main() {
    solve(0);
    cout << "共找到解的數量：" << totalSolutions << endl;
    return 0;
}
