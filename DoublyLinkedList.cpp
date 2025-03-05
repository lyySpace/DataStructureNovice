#include <iostream>
using namespace std;

struct Node {
    int data;      
    Node* prev;    
    Node* next;   
    Node(int d) : data(d), prev(nullptr), next(nullptr) {}
};

// print!!!
void printDoublyList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " <-> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

// Inserting a node at the beginning
void insertAtBeginning(Node*& head, int new_data) {
    Node* new_node = new Node(new_data);
    new_node->prev = nullptr; 
    new_node->next = head;
    
    if (head != nullptr) {
        head->prev = new_node;
    }
    
    head = new_node;
}

// Inserting a node at the end
void insertAtEnd(Node*& head, int new_data) {
    Node* new_node = new Node(new_data);
    new_node->next = nullptr; 
    if (head == nullptr) {
        new_node->prev = nullptr;
        head = new_node;
        return;
    }

    Node* current = head;
    while (current->next != nullptr){
        current = current->next;
    }
    current->next = new_node;
    new_node->prev = current;
}

// Inserting a node After a Given Node
void insertAfter(Node*& head, int givenNode, int new_data){
    Node* new_node = new Node(new_data);

    Node* current = head;
    while (current->next != nullptr){
        if (current->data == givenNode){
            new_node->next = current->next;
            new_node->prev = current;
            current->next->prev = new_node;
            current->next = new_node;
            return;

        }
        current = current->next;
    }
    if (current->data == givenNode){
        insertAtEnd(current, new_data);
    }
    else{
        cout << "not found the given node\n";
    }
}

// Inserting a node Before a Given Node
void insertBefore(Node*& head, int givenNode, int new_data){
    Node* new_node = new Node(new_data);

    Node* current = head;
    if (current->data == givenNode){
        insertAtBeginning(current, new_data);
        return;
    }
    while (current->next != nullptr){
        if (current->data == givenNode){
            new_node->next = current;
            new_node->prev = current->prev;
            current->prev->next = new_node;
            current->prev = new_node;
            return;

        }
        current = current->next;
    }
    cout << "not found the given node\n";
}

// Deleting the First Node 

int main() {
    Node* head = nullptr;
    
    // 10 20 30
    insertAtBeginning(head, 10);
    insertAtBeginning(head, 20);
    insertAtBeginning(head, 30);
    
    insertAtEnd(head,05);

    insertAfter(head,20,77);
    insertBefore(head,10,66);

    printDoublyList(head);
    
    // clear
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}