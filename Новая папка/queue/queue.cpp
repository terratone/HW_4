//  Реализовать шаблонный класс "Очередь" на основе двусвязного списка

#include <iostream>

using namespace std;

// Определение узла списка
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    // Конструктор узла
    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

// Определение класса очереди
template <typename T>
class Queue {
private:
    Node<T>* front; // Первый элемент очереди
    Node<T>* rear; // Последний элемент очереди

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Проверка очереди на пустоту
    bool isEmpty() {
        return front == nullptr;
    }

    // Добавление элемента в очередь
    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value); // Создаем новый узел
        if (isEmpty()) {
            front = rear = newNode; // Если очередь пуста, новый узел становится и первым, и последним
        }
        else {
            rear->next = newNode; // Указываем, что текущий последний элемент указывает на новый узел
            newNode->prev = rear; // Устанавливаем указатель на предыдущий элемент для нового узла
            rear = newNode; // Переназначаем указатель на последний элемент на новый узел
        }
    }

    // Извлечение элемента из очереди
    T dequeue() {
        if (isEmpty()) {
            cout << "the queue is empty" << endl;
            return T(); // Возвращаем пустое значение типа T, если очередь пуста
        }
        Node<T>* temp = front; // Сохраняем указатель на первый элемент
        T dequeuedData = front->data; // Сохраняем данные первого элемента
        if (front == rear) {
            front = rear = nullptr; // Если очередь содержит только один элемент, обнуляем указатели
        }
        else {
            front = front->next; // Переназначаем указатель на первый элемент
            front->prev = nullptr; // Обнуляем указатель на предыдущий элемент у нового первого элемента
        }
        delete temp; // Освобождаем память, занимаемую первым элементом
        return dequeuedData; // Возвращаем данные извлеченного элемента
    }

    // Получение первого элемента очереди
    T getFront() {
        if (isEmpty()) {
            cout << "the queue is empty" << endl;
            return T(); // Возвращаем пустое значение типа T, если очередь пуста
        }
        return front->data; // Возвращаем данные первого элемента
    }
};

int main() {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    cout << "First element: " << queue.getFront() << endl;
    cout << "Retrieved element: " << queue.dequeue() << endl;
    cout << "Retrieved element: " << queue.dequeue() << endl;
    cout << "Retrieved element: " << queue.dequeue() << endl;
    
    return 0;
}