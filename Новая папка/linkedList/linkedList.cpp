//  Подсчитать, сколько раз каждое
//  слово встречается в заданном тексте.
//  Результат записать в коллекцию
//  Dictionary<TKey, TValue>
#include <iostream>

using namespace std;

// Определение узла списка
class Node {
public:
    int data;
    Node* next;

    // Конструктор узла
    Node(int value) : data(value), next(nullptr) {}
};

// Определение класса стека
class Stack {
private:
    Node* top; // Верхний элемент стека

public:
    Stack() : top(nullptr) {}

    // Проверка стека на пустоту
    bool isEmpty() {
        return top == nullptr;
    }

    // Добавление элемента в стек
    void push(int value) {
        Node* newNode = new Node(value); // Создаем новый узел
        newNode->next = top; // Устанавливаем указатель на следующий элемент на текущий верхний элемент
        top = newNode; // Переназначаем верхний элемент на новый узел
    }

    // Извлечение верхнего элемента из стека
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1; // Возвращаем значение -1, если стек пуст
        }
        Node* temp = top; // Сохраняем указатель на верхний элемент
        int poppedData = top->data; // Сохраняем данные верхнего элемента
        top = top->next; // Переназначаем верхний элемент на следующий элемент
        delete temp; // Освобождаем память, занимаемую верхним элементом
        return poppedData; // Возвращаем данные верхнего элемента
    }

    // Получение верхнего элемента стека
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1; // Возвращаем значение -1, если стек пуст
        }
        return top->data; // Возвращаем данные верхнего элемента
    }
};

int main() {
    Stack stack;
    cout << boolalpha;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << "Stack is empty?: " << stack.isEmpty() << endl;
    cout << "Element at the top: " << stack.peek() << endl;
    cout << "Retrieved element: " << stack.pop() << endl;
    cout << "Retrieved element: " << stack.pop() << endl;
    cout << "Retrieved element: " << stack.pop() << endl;

    cout << "Stack is empty?: " << stack.isEmpty() << endl;

    return 0;
}