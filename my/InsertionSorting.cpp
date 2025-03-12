#include <iostream>
#include <list>
using namespace std;

// Array-based list
class ArrayList {
private:
    int* arr;     
    int capacity;  
    int size;     

public:
    // 建構子
    ArrayList(int cap) : capacity(cap), size(0) {
        arr = new int[capacity];
    }

    // 解構子
    ~ArrayList() {
        delete[] arr;
    }

    void add(int value) {
        if (size < capacity) {
            arr[size++] = value;
        } else {
            cout << "Filled" << endl;
        }
    }

    void insertionSortArray() {
        for (int i = 1; i < size; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // print!
    void printArray() const {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};


// Singly Linked List-based List
class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
    
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;
    
public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void insertionSortLinkedList(){
        if (head == nullptr || head->next == nullptr)
            return;

        Node* sorted = nullptr;  // 新建立的排序後的串列

        // 逐一取出原串列中的節點
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;  // 暫存下一個節點

            // 若 sorted 為空，或 current 節點應插入到 sorted 的最前端
            if (sorted == nullptr || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                // 找到在 sorted 中的正確位置插入 current 節點
                Node* temp = sorted;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;  // 處理下一個節點
        }
        head = sorted;  // 更新 head 指向排序後的串列

    }

    void printLinkedList() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    ArrayList list(10);
    list.add(34);
    list.add(7);
    list.add(23);
    list.add(32);
    list.add(5);
    list.add(62);

    cout << "Array-based list\n";
    cout << "before: ";
    list.printArray();
    list.insertionSortArray();
    cout << "after: ";
    list.printArray();

    cout << "-------------------------------\n";

    LinkedList list1;
    list1.append(20);
    list1.append(60);
    list1.append(30);
    list1.append(10);
    
    cout << "Singly Linked List-based List\n";
    cout << "before: ";
    list1.printLinkedList();
    list1.insertionSortLinkedList();
    cout << "after: ";
    list1.printLinkedList();

    return 0;
}
