#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <random>
#include <ctime>
using namespace std;

const int HTSize = 59;
const int N = 25;

int keys[N] = {
    10102109, 10106402, 10106918, 12508729, 12508629, 12508765,
    12508068, 12508705, 12508842, 11508011, 11508817, 11508388,
    11508189, 11508331, 11508675, 11508521, 11508287, 11508863,
    11508979, 11508532, 11508035, 11508599, 10613285, 13945978,
    12945157
};

// ------------------------ PART A ------------------------
// Division(Modular) Hashing + Random Probing

void partA() {
    vector<int> table(HTSize, -1);
    vector<int> offset;
    for (int i = 1; i < HTSize; ++i) offset.push_back(i);
    default_random_engine rng(42);  
    shuffle(offset.begin(), offset.end(), rng);

    cout << "[Part A] Division(Modular) Hashing + Random Probing\n";
    int totalCollisions = 0;

    for (int k : keys) {
        int h = k % HTSize;
        int collisions = 0;

        if (table[h] == -1) {
            table[h] = k;
            cout << k << " -> " << h << "\n";
            continue;
        }

        bool inserted = false;
        for (int i = 0; i < offset.size(); ++i) {
            int index = (h + offset[i]) % HTSize;
            ++collisions;
            if (table[index] == -1) {
                table[index] = k;
                cout << k << " -> " << index << " (collision at " << h << ", ri=" << offset[i] << ")\n";
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            cout << k << " -> FAILED\n";
        }
        totalCollisions += collisions;
    }
    cout << "Total collisions: " << totalCollisions << "\n\n";
}

// ------------------------ PART B ------------------------
// Mid-Square Hashing + Double Hashing

int midSquareHash(int key) {
    long long square = 1LL * key * key;
    string s = to_string(square);
    int len = s.size();
    int mid = len / 2;
    int extracted = stoi(s.substr(mid - 2, 4)); // 取中間4位
    return extracted % HTSize;
}

int secondHash(int key) {
    return 1 + (key % 53); // 53 為小於 59 的質數
}

void partB() {
    vector<int> table(HTSize, -1);

    cout << "[Part B] Mid-Square Hashing + Double Hashing\n";
    int totalCollisions = 0;

    for (int k : keys) {
        int h1 = midSquareHash(k);
        int h2 = secondHash(k);
        int collisions = 0;

        int index = h1;
        while (table[index] != -1) {
            ++collisions;
            index = (h1 + collisions * h2) % HTSize;
        }
        table[index] = k;

        if (collisions == 0)
            cout << k << " -> " << index << "\n";
        else
            cout << k << " -> " << index << " (" << collisions << " collisions, h2=" << h2 << ")\n";

        totalCollisions += collisions;
    }
    cout << "Total collisions: " << totalCollisions << "\n";
}

int main() {
    srand(42); // 為 reproducibility 固定隨機序列
    partA();
    partB();
    return 0;
}
