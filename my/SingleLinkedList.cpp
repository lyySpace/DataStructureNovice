#include <iostream>
using namespace std;

struct Node {
    int data;      
    Node* next;    

    // 建構子初始化
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};

// print!!!
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

// Single Linhed Lists: Searching for a Value
bool search(Node* head, int key) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == key) {
            cout << "Find it!\n";
            return true;
        }
        current = current->next;
    }
    cout << "Soo Sad, not found\n";
    return false;
}

// Inserting a Node at the Beginning
void insertAtBeginning(Node*& head, int newData) {
    Node* newNode = new Node(newData);
    newNode->next = head;
    head = newNode;
}

// Inserting a Node at the End
void insertAtEnd(Node*& head, int newData) {
    Node* newNode = new Node(newData);
    if (head == nullptr) {
        head = newNode;
        return;
    } 
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

// Inserting a Node after a Given Node
void insertAfter(Node*& head, int givenNode, int newData) {
    Node* newNode = new Node(newData);
    Node* current = head;
    while (current->next != nullptr) {
        if (current->data == givenNode){
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }
    if (current->data == givenNode){
        insertAtEnd(current, newData);
    }
    else{
        cout << "not found the given node\n";
    }
}

// Inserting a Node before a Given Node
void insertbefore(Node*& head, int givenNode, int newData) {
    if (head->data == givenNode){
        insertAtBeginning(head, newData);
        return;
    }
    Node* newNode = new Node(newData);
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data == givenNode){
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        else {
            current = current->next;
        }
    }
    cout << "not found the given node\n";
}

// Deleting the First Node
void deleteFirst(Node*& head) {
    if (head == nullptr) {
        cout << "original is null" << endl;
        return;
    }
    Node* temp = head; 
    head = head->next;
    delete temp;      
}

// Deleting the Last Node
void deleteLast(Node*& head) {
    if (head == nullptr) {
        cout << "original is null" << endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }

    Node* temp = current->next; 
    current->next = nullptr;
    delete temp;      
}

// Deleting a Node after a Given Node
void deleteAfter(Node*& head, int givenNode){
    Node* current = head;
    while (current->next != nullptr) {
        if (current->data == givenNode){
            Node* temp = current->next;
            if (temp->next == nullptr){
                deleteLast(head);
                return;
            }
            current->next = current->next->next;
            delete temp; 
            return;
        }
        current = current->next;
    }
    if (current->data == givenNode){
        cout << "given node cannot be the last\n";
    }
    else{
        cout << "not found the given node\n";
    }
}

int main() {
    Node* head = nullptr;
    // 30 -> 20 -> 10 -> 40
    insertAtBeginning(head, 10);
    insertAtBeginning(head, 20);
    insertAtBeginning(head, 30);
    insertAtEnd(head, 40);
    printList(head);

    // Searching for a Value
    int key = 30;
    search(head, key);

    // 30 -> 20 -> 77 -> 10 -> 44 -> 40
    insertAfter(head, 10, 44);
    insertbefore(head, 10, 77);
    printList(head);

    // 20 -> 77 -> 10 
    deleteFirst(head);
    deleteLast(head);
    deleteAfter(head, 10);
    printList(head);

    
    // 釋放記憶體
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
