#include <iostream>
#include <vector>
using namespace std;

// 給你一個 2D 區域（如圖片或迷宮），從某個點開始，將與它連續相同顏色的區塊改成新顏色
void floodFillRec(vector<vector<int>>& image, int x, int y, int oldColor, int newColor) {
    int rows = image.size();
    int cols = image[0].size();

    // 越界 or 顏色不同 → 不填
    if (x < 0 || x >= rows || y < 0 || y >= cols || image[x][y] != oldColor)
        return;

    // 填色
    image[x][y] = newColor;

    // 遞迴四方向
    floodFillRec(image, x + 1, y, oldColor, newColor);
    floodFillRec(image, x - 1, y, oldColor, newColor);
    floodFillRec(image, x, y + 1, oldColor, newColor);
    floodFillRec(image, x, y - 1, oldColor, newColor);
}

void floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];  // 取得起始點的顏色
    if (oldColor == newColor) return; // 不用處理

    floodFillRec(image, sr, sc, oldColor, newColor);
}

// 印出整張圖
void printImage(const vector<vector<int>>& image) {
    for (const auto& row : image) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<int>> image = {
        {1, 1, 1, 2},
        {1, 1, 1, 2},
        {1, 0, 1, 2},
        {1, 0, 0, 1}
    };

    int sr = 1, sc = 1;  // 起點
    int newColor = 9;

    cout << "原圖：" << endl;
    printImage(image);

    floodFill(image, sr, sc, newColor);

    cout << "\n填色後: " << endl;
    printImage(image);

    return 0;
}
