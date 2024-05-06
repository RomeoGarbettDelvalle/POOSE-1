#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <vector>

namespace ProjectAlpha
{
    //Teilaufgabe 1 (Romeo): Implementierung der abstrakten Klassen //fertig
    //Teilaufgabe 2 (Romeo): Implementierung der LinkedListStack und SinglyLinkedList //fertig
    //Teilaufgabe 3 (Gabriel): Implementierung der LinkedListQueue und SinglyLinkedList //halb fertig
    //Teilaufgabe 4 (Vincent): Implementierung der DoublyLinkedList, HeapPriorityQueue und HashSet //fertig
    //Teilaufgabe 5 (Romeo): Implementierung von JUnit Tests //bin ich dran
    //Teilaufgabe 5 (muss noch eingeteilt werden): Iteratoren //noch nicht angefangen


    // Abstract base interface for all collections
    template<typename T>
    class AbstractCollection {
    public:
        virtual bool contains(T element) = 0;
        virtual int size() = 0;
        virtual ~AbstractCollection() {}
    };

    // Abstract interface for stacks
    template<typename T>
    class AbstractStack : public AbstractCollection<T> {
    public:
        virtual T push(T element) = 0;
        virtual T pop() = 0;
        virtual T peek() = 0;
    };

    // Abstract interface for queues
    template<typename T>
    class AbstractQueue : public AbstractCollection<T> {
    public:
        virtual T enqueue(T element) = 0;
        virtual T dequeue() = 0;
        virtual T peek() = 0;
    };

    // Abstract interface for lists
    template<typename T>
    class AbstractList : public AbstractCollection<T> {
    public:
        virtual void add(int index, T element) = 0;
        virtual T remove(int index) = 0;
        virtual T get(int index) = 0;
        virtual void set(int index, T element) = 0;
    };

    // Abstract interface for priority queues
    template<typename T>
    class AbstractPriorityQueue : public AbstractCollection<T> {
    public:
        virtual T enqueue(T element) = 0;
        virtual T dequeue() = 0;
        virtual T peek() = 0;
    };

    // Abstract interface for sets
    template<typename T>
    class AbstractSet : public AbstractCollection<T> {
    public:
        virtual bool isEmpty() = 0;
    };

    // Abstract interface for hash sets
    template<typename T>
    class AbstractHashSet : public AbstractSet<T> {
    public:
        virtual int hashCode(T element) = 0;
    };

    // Abstract interface for ordered sets
    template<typename T>
    class AbstractOrderedSet : public AbstractSet<T> {
    public:
        virtual T get(int index) = 0;
    };

    // Concrete implementation of a stack using a linked list
    template<typename T>
    class LinkedListStack : public ProjectAlpha::AbstractStack<T> {
    private:
        struct Node {
            T data;
            Node* next;
        };
        Node* top;
    public:
        LinkedListStack() { top = nullptr; }
        ~LinkedListStack() {
            while (top != nullptr) {
                Node* temp = top;
                top = top->next;
                delete temp;
            }
        }
        T push(T element) override {
            Node* newNode = new Node;
            newNode->data = element;
            newNode->next = top;
            top = newNode;
            return element;
        }
        T pop() override {
            if (isEmpty()) {
                throw std::runtime_error("Stack is empty");
            }
            T data = top->data;
            Node* temp = top;
            top = top->next;
            delete temp;
            return data;
        }
        T peek() override {
            if (isEmpty()) {
                throw std::runtime_error("Stack is empty");
            }
            return top->data;
        }
        bool contains(T element) override {
            Node* current = top;
            while (current != nullptr) {
                if (current->data == element) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
        int size() override {
            int count = 0;
            Node* current = top;
            while (current != nullptr) {
                count++;
                current = current->next;
            }
            return count;
        }
        bool isEmpty() {
            return top == nullptr;
        }
    };

    // Concrete implementation of a queue using a linked list
    template<typename T>
    class LinkedListQueue : public ProjectAlpha::AbstractQueue<T> {
        private:
        struct Node {
            T data;
            Node* next;
        };
        Node* front;
        Node* rear;
        public:
        LinkedListQueue() { front = nullptr; rear = nullptr; }
        ~LinkedListQueue() {
            while (front != nullptr) {
                Node* temp = front;
                front = front->next;
                delete temp;
            }
        }
        T enqueue(T element) {
            Node* newNode = new Node;
            newNode->data = element;
            newNode->next = nullptr;
            if (rear == nullptr) {
                front = rear = newNode;
                return element;
            }
            rear->next = newNode;
            rear = newNode;
            return element;
        }
        T dequeue() {
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty");
            }
            T data = front->data;
            Node* temp = front;
            front = front->next;
            if (front == nullptr) {
                rear = nullptr;
            }
            delete temp;
            return data;
        }
        T peek() {
            if (isEmpty()) {
                throw std::runtime_error("Queue is empty");
            }
            return front->data;
        }
        bool isEmpty() {
            return front == nullptr;
        }
        bool contains(T element) override {
            Node* current = front;
            while (current != nullptr) {
                if (current->data == element) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        int size() override {
            int count = 0;
            Node* current = front;
            while (current != nullptr) {
                count++;
                current = current->next;
            }
            return count;
        }
    };

    // Concrete implementation of a singly linked list
    template<typename T>
    class SinglyLinkedList : public ProjectAlpha::AbstractList<T> {
        // implementation details
    };

    // Concrete implementation of a doubly linked list
    template<typename T>
    class DoublyLinkedList : public ProjectAlpha::AbstractList<T> {
    private:
        struct Node {
            T data;
            Node* prev;
            Node* next;
            Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
        };
        Node* head;
        Node* tail;
        int count;
    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

        ~DoublyLinkedList() {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void add(int index, T element) override {
            if (index < 0 || index > count) {
                throw std::out_of_range("Index out of range");
            }
            if (index == 0) {
                Node* newNode = new Node(element);
                newNode->next = head;
                if (head != nullptr) {
                    head->prev = newNode;
                }
                head = newNode;
                if (tail == nullptr) {
                    tail = newNode;
                }
            } else if (index == count) {
                Node* newNode = new Node(element);
                newNode->prev = tail;
                if (tail != nullptr) {
                    tail->next = newNode;
                }
                tail = newNode;
                if (head == nullptr) {
                    head = newNode;
                }
            } else {
                Node* current = head;
                for (int i = 0; i < index; ++i) {
                    current = current->next;
                }
                Node* newNode = new Node(element);
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev->next = newNode;
                current->prev = newNode;
            }
            count++;
        }

        T remove(int index) override {
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            T removedData = current->data;
            if (current->prev == nullptr) {
                head = current->next;
            } else {
                current->prev->next = current->next;
            }
            if (current->next == nullptr) {
                tail = current->prev;
            } else {
                current->next->prev = current->prev;
            }
            delete current;
            count--;
            return removedData;
        }

        T get(int index) override {
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->data;
        }

        void set(int index, T element) override {
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }
            Node* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            current->data = element;
        }

        bool contains(T element) override {
            Node* current = head;
            while (current != nullptr) {
                if (current->data == element) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        int size() override {
            return count;
        }
    };

    // Concrete implementation of a priority queue using a heap
    template<typename T>
    class HeapPriorityQueue : public ProjectAlpha::AbstractPriorityQueue<T> {
        private:
        std::vector<T> heap;
    public:
        T enqueue(T element) override {
            heap.push_back(element);
            int index = heap.size() - 1;
            while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
                std::swap(heap[index], heap[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
            return element;
        }

        T dequeue() override {
            if (heap.empty()) {
                throw std::runtime_error("Priority queue is empty");
            }
            T maxElement = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            int index = 0;
            while (true) {
                int leftChildIndex = 2 * index + 1;
                int rightChildIndex = 2 * index + 2;
                int largestIndex = index;
                if (leftChildIndex < heap.size() && heap[leftChildIndex] > heap[largestIndex]) {
                    largestIndex = leftChildIndex;
                }
                if (rightChildIndex < heap.size() && heap[rightChildIndex] > heap[largestIndex]) {
                    largestIndex = rightChildIndex;
                }
                if (largestIndex == index) {
                    break;
                }
                std::swap(heap[index], heap[largestIndex]);
                index = largestIndex;
            }
            return maxElement;
        }

        T peek() override {
            if (heap.empty()) {
                throw std::runtime_error("Priority queue is empty");
            }
            return heap[0];
        }

        bool contains(T element) override {
            for (const auto& item : heap) {
                if (item == element) {
                    return true;
                }
            }
            return false;
        }

        int size() override {
            return heap.size();
        }
    };

    // Concrete implementation of a hash set using a hash table
    template<typename T>
    class HashSet : public ProjectAlpha::AbstractHashSet<T> {
         private:
        std::unordered_set<T> hashSet;
    public:
        int hashCode(T element) override {
            // Simple hash function for demonstration purposes
            return std::hash<T>{}(element);
        }

        bool contains(T element) override {
            return hashSet.find(element) != hashSet.end();
        }

        bool isEmpty() override {
            return hashSet.empty();
        }
    };
\
}


int main() {
    // test usage of the LinkedListQueue
    ProjectAlpha::LinkedListQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "Dequeued: " << queue.dequeue() << std::endl; // expected Ausgabe: 1
    std::cout << "Queue size: " << queue.size() << std::endl; // expected Ausgabe: 2
    std::cout << "Queue contains 2: " << std::boolalpha << queue.contains(2) << std::endl; // expected Ausgabe: true
    std::cout << "Queue contains 4: " << std::boolalpha << queue.contains(4) << std::endl; // expected Ausgabe: false

    // test usage for the LinkedListStack
    ProjectAlpha:: LinkedListStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << stack.peek() << "\n"; // expected Ausgabe: 3
    stack.pop();
    std::cout << stack.peek(); // expected Ausgabe: 2
    std::cout << stack.contains(1) << "\n"; // expected Ausgabe: 0
    std::cout << stack.size() << "\n"; // expected Ausgabe: 2
    stack.pop();
    stack.pop();
    std::cout << stack.isEmpty() << "\n"; // expected Ausgabe: 1
    return 0;

    // Test der SinglyLinkedList
    //has jet to be implemented

    // Test der DoublyLinkedList
    ProjectAlpha::DoublyLinkedList<int> list;
    list.add(0, 1);
    list.add(1, 2);
    list.add(2, 3);
    list.add(1, 4); // Fügt 4 an der Position 1 ein
    std::cout << "List size: " << list.size() << std::endl; // Ausgabe: 4

    std::cout << "List elements: ";
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list.get(i) << " ";
    }
    std::cout << std::endl; // Ausgabe: 1 4 2 3

    list.remove(1); // Entfernt das Element an der Position 1
    std::cout << "List size after removal: " << list.size() << std::endl; // Ausgabe: 3

    // Test der HeapPriorityQueue
    ProjectAlpha::HeapPriorityQueue<int> priorityQueue;
    priorityQueue.enqueue(5);
    priorityQueue.enqueue(10);
    priorityQueue.enqueue(3);
    priorityQueue.enqueue(7);
    std::cout << "Priority queue size: " << priorityQueue.size() << std::endl; // Ausgabe: 4
    std::cout << "Dequeued max element: " << priorityQueue.dequeue() << std::endl; // Ausgabe: 10

    // Test der HashSet
    ProjectAlpha::HashSet<std::string> hashSet;
    hashSet.hashCode("apple");
    hashSet.hashCode("banana");
    hashSet.hashCode("orange");
    std::cout << "HashSet contains 'banana': " << std::boolalpha << hashSet.contains("banana") << std::endl; // Ausgabe: true
    std::cout << "HashSet contains 'grape': " << std::boolalpha << hashSet.contains("grape") << std::endl; // Ausgabe: false

    return 0;
}
