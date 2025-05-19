#include <iostream>
using namespace std;

template <class Type>
struct Node {
    Type info;
    Node<Type>* link;
};

template <class Type>
class LinkedStack {
private:
    Node<Type>* stackTop;  // 指向堆疊頂端

public:
    // Constructor
    LinkedStack() {
        stackTop = nullptr;
    }

    // Destructor
    ~LinkedStack() {
        initializeStack(); // 清空堆疊
    }

    // 初始化（清空堆疊）
    void initializeStack() {
        Node<Type>* temp;
        while (stackTop != nullptr) {
            temp = stackTop;
            stackTop = stackTop->link;
            delete temp;
        }
    }

    // 判斷是否為空
    bool isEmptyStack() const {
        return stackTop == nullptr;
    }

    // push
    void push(const Type& newItem) {
        Node<Type>* newNode = new Node<Type>;
        newNode->info = newItem;
        newNode->link = stackTop;
        stackTop = newNode;
    }

    // top
    Type top() const {
        if (isEmptyStack()) {
            cerr << "Stack is empty." << endl;
            exit(1);
        }
        return stackTop->info;
    }

    // pop
    void pop() {
        if (isEmptyStack()) {
            cerr << "Stack is empty. Cannot pop." << endl;
            return;
        }
        Node<Type>* temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }

    // 額外：列印 stack（從 top 到 bottom）
    void printStack() const {
        Node<Type>* current = stackTop;
        while (current != nullptr) {
            cout << current->info << " ";
            current = current->link;
        }
        cout << endl;
    }
};

int main() {
    LinkedStack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "目前 stack: ";
    s.printStack();  // 應該印出：30 20 10

    cout << "Top element: " << s.top() << endl; // 印出 30

    s.pop();  // 移除頂部 30
    cout << "After pop: ";
    s.printStack();  // 應該印出：20 10

    s.initializeStack(); // 清空堆疊
    cout << "After initialize: ";
    s.printStack();  // 應該印出空行

    return 0;
}
