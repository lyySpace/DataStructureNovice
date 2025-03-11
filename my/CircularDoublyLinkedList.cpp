#include <iostream>
using namespace std;

struct Node {
    int data;      
    Node* prev;    
    Node* next;   
    Node(int d) : data(d), prev(nullptr), next(nullptr) {}
};

// print!!
void printCircularDoublyList(Node*& head) {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    
    Node* temp = head;
    do {
        cout << temp->data << " <-> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to head)" << endl;
}

// Inserting a Node at the beginning
void insertAtBeginning(Node*& head, int new_data) {
    Node* new_node = new Node(new_data);
    if (head == nullptr) {
        head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return;
    }

    Node* tail = head->prev;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
}

// Inserting a Node at the End
void insertAtEnd(Node*& head, int new_data) {
    Node* new_node = new Node(new_data);
    if (head == nullptr) {
        head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return;
    }

    Node* tail = head->prev;
    tail->next = new_node;
    new_node->prev = tail;
    new_node->next = head;
    head->prev = new_node;
}

// deleting the First Node
void deleteFirst(Node*& head){
    Node* temp = head;
    Node* tail = head->prev;
    tail->next = head->next; 
    head->next->prev = tail;
    delete temp;
    head = tail->next;
}

// deleting the Last Node
void deleteLast(Node*& head){
    Node* temp = head->prev;
    temp->prev->next = head; 
    head->prev = temp->prev;
    delete temp;
}

int main() {
    Node* head = nullptr;
    
    // 10 20 30
    insertAtBeginning(head, 10);
    insertAtBeginning(head, 20);
    insertAtBeginning(head, 30);
    
    // 10 20 30 50
    insertAtEnd(head,50);

    deleteLast(head);

    printCircularDoublyList(head);

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

