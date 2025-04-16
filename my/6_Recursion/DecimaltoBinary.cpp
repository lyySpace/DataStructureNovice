#include <iostream>
using namespace std;

void decToBin(int num, int base) {
    if (num > 0) {
        decToBin(num / base, base);
        cout << num % base;
    }
}

int main() {
    int num = 35;
    cout << "Binary of " << num << " = ";
    decToBin(num, 2);
    cout << endl;

    cout << "Octal of " << num << " = ";
    decToBin(num, 8);
    cout << endl;

    return 0;
}
