#include <iostream>
using namespace std;

int largest(const int list[], int lowerIndex, int upperIndex) {
    int max;

    if (lowerIndex == upperIndex)  
        return list[lowerIndex];
    else {
        max = largest(list, lowerIndex + 1, upperIndex);  
        if (list[lowerIndex] >= max)
            return list[lowerIndex];
        else
            return max;
    }
}

int main() {
    int n;

    cout << "請輸入陣列大小：";
    cin >> n;

    int list[n];  

    cout << "請輸入 " << n << " 個整數：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> list[i];
    }

    int maxValue = largest(list, 0, n - 1);

    cout << "陣列中的最大值為：" << maxValue << endl;

    return 0;
}
