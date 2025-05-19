#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 100;

template <class Type>
class stackType {
private:
    Type* list;
    int stackTop;
    int maxStackSize;

    void copyStack(const stackType<Type>& otherStack) {
        delete[] list; // 清空原本的
        maxStackSize = otherStack.maxStackSize;
        stackTop = otherStack.stackTop;
        list = new Type[maxStackSize];
        for (int i = 0; i < stackTop; i++)
            list[i] = otherStack.list[i];
    }

public:
    // Constructor
    stackType(int size = DEFAULT_SIZE) {
        maxStackSize = size;
        stackTop = 0;
        list = new Type[maxStackSize];
    }

    // Destructor
    ~stackType() {
        delete[] list;
    }

    // Copy constructor
    stackType(const stackType<Type>& otherStack) {
        list = nullptr;
        copyStack(otherStack);
    }

    // Assignment operator
    stackType<Type>& operator=(const stackType<Type>& otherStack) {
        if (this != &otherStack) {
            copyStack(otherStack);
        }
        return *this;
    }

    // Stack operations
    bool isEmptyStack() const {
        return stackTop == 0;
    }

    bool isFullStack() const {
        return stackTop == maxStackSize;
    }

    void push(Type item) {
        if (!isFullStack())
            list[stackTop++] = item;
        else
            cout << "Stack is full.\n";
    }

    void pop() {
        if (!isEmptyStack())
            stackTop--;
        else
            cout << "Stack is empty.\n";
    }

    Type top() const {
        if (!isEmptyStack())
            return list[stackTop - 1];
        else {
            cout << "Stack is empty.\n";
            return Type();
        }
    }

    void printStack() const {
        for (int i = stackTop - 1; i >= 0; i--)
            cout << list[i] << " ";
        cout << endl;
    }
};

// === 測試主程式 ===
int main() {
    stackType<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    cout << "s1 原始 stack: ";
    s1.printStack();  // 應該印出：30 20 10

    // 用 copy constructor 建立 s2
    stackType<int> s2(s1);
    cout << "s2 (copy constructor): ";
    s2.printStack();  // 應該也印出：30 20 10

    // 用賦值運算子建立 s3
    stackType<int> s3;
    s3 = s1;
    cout << "s3 (assignment =): ";
    s3.printStack();  // 應該也印出：30 20 10

    // 修改 s1 應不影響 s2/s3（深拷貝驗證）
    s1.pop();
    s1.pop();
    cout << "s1 after pop 2 times: ";
    s1.printStack();  // 印出：10

    cout << "s2 unchanged: ";
    s2.printStack();  // 應還是：30 20 10

    cout << "s3 unchanged: ";
    s3.printStack();  // 應還是：30 20 10

    return 0;
}


