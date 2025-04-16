#include <iostream>
using namespace std;

template <class Type>
struct nodeType {
    Type data;
    nodeType<Type>* next;
};

template <class Type>
class linkedListType {
public:
    linkedListType() {
        head = NULL;  
    }
    ~linkedListType() {
        nodeType<Type>* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;  
        }
    }  

    void insertFirst(Type newItem){
        nodeType<Type>* newNode = new nodeType<Type>;
        newNode->data = newItem;
        newNode->next = head;
        head = newNode;
    }     

    void reversePrint() const{ // 外部接口函式
        reversePrint(head);
        cout << endl;
    }

private:
    nodeType<Type>* head;                 
    void reversePrint(nodeType<Type>* current) const{ // 內部遞迴函式
        if (current != NULL) {
            reversePrint(current->next);            
            cout << current->data << " ";           
        }
    }
};


int main() {
    linkedListType<int> list;

    // 40 30 20 10
    list.insertFirst(10);
    list.insertFirst(20);
    list.insertFirst(30);
    list.insertFirst(40);

    cout << "Reverse Print linked list: ";
    list.reversePrint();  // 10 20 30 40

    return 0;
}
