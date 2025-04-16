#include <iostream>
#include <vector>
using namespace std;

void subsetSums(const vector<int>& arr, int index, int currentSum) {
    // base case：所有元素都看過了
    if (index == arr.size()) {
        cout << currentSum << " ";
        return;
    }

    // 選擇：包含 arr[index]
    subsetSums(arr, index + 1, currentSum + arr[index]);

    // 選擇：不包含 arr[index]
    subsetSums(arr, index + 1, currentSum);
}

int main() {
    vector<int> arr = {1, 2, 3};

    cout << "所有子集合的總和：" << endl;
    subsetSums(arr, 0, 0);  // 從第 0 個開始，初始 sum 為 0
    cout << endl;

    return 0;
}
