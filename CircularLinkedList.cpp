#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// print!!!
void printCircularList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* current = head;
    do {
        cout << current->data << " -> ";
        current = current->next;
    } while (current != head);
    cout << "(back to head)" << endl;
}

// Inserting a Node at the Beginning
void insertAtBeginning(Node*& head, int newData) {
    Node* newNode = new Node(newData);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        return;
    }
    
    Node* current = head;
    while (current->next != head) {
        current = current->next;
    }
    newNode->next = head;
    head = newNode;
    current->next = head;
}

// Inserting a Node at the End
void insertAtEnd(Node*& head, int newData) {
    Node* newNode = new Node(newData);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
        return;
    }
    
    Node* current = head;
    while (current->next != head) {
        current = current->next;
    }
    current->next = newNode;
    newNode->next = head;
}

// Deleting the First Node
void deleteFirst(Node*& head) {
    if (head == nullptr) {
        cout << "original is null" << endl;
        return;
    }
    if (head->next == head) {
        delete head;
        head = nullptr;
        return;
    }
    Node* current = head;
    while (current->next != head) {
        current = current->next;
    }
    Node* temp = head;
    head = head->next;
    current->next = head;
    delete temp;
}

// Deleting the Last Node
void deleteLast(Node*& head) {
    if (head == nullptr) {
        cout << "original is null" << endl;
        return;
    }
    if (head->next == head) {
        delete head;
        head = nullptr;
        return;
    }
    Node* current = head;
    while (current->next->next != head) {
        current = current->next;
    }
    Node* temp = current->next;
    current->next = head;
    delete temp;
}

int main() {
    Node* head = nullptr;
    
    insertAtEnd(head, 10);
    insertAtEnd(head, 20);
    insertAtEnd(head, 30);
    
    deleteFirst(head);
    insertAtBeginning(head,10);
    deleteLast(head);

    printCircularList(head);
    
    // 釋放記憶體需要特別處理圓形結構
    if (head != nullptr) {
        Node* current = head->next;
        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }
    return 0;
}