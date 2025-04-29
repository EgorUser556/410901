#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    srand(time(0)); //Инициализация генератора случайных чисел

    //Создаем список из 10 случайных чисел (от 0 до 99)
    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < 10; i++) {
        Node* newNode = new Node;
        newNode->data = rand() % 100;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    //Выводим исходный список
    cout << "Original list: ";
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    //Находим узел с минимальным значением
    Node* minNode = head;
    Node* temp = head->next;

    while (temp != nullptr) {
        if (temp->data < minNode->data) {
            minNode = temp;
        }
        temp = temp->next;
    }
    cout << "Min value: " << minNode->data << endl;

    //Создаем новый список для элементов между головой и minNode
    Node* newListHead = nullptr;
    Node* newListTail = nullptr;

    current = head->next; // Начинаем с элемента после головы
    while (current != minNode && current != nullptr) {
        // Создаем копию текущего узла для нового списка
        Node* newNode = new Node;
        newNode->data = current->data;
        newNode->next = nullptr;

        if (newListHead == nullptr) {
            newListHead = newNode;
            newListTail = newNode;
        }
        else {
            newListTail->next = newNode;
            newListTail = newNode;
        }

        current = current->next;
    }

    //Выводим новый список
    cout << "Elements between head and min: ";
    current = newListHead;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
    return 0;
}   
