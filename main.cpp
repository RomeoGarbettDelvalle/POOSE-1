#include <iostream>
namespace ProjectAlpha
{
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
        // implementation details
    };

    // Concrete implementation of a priority queue using a heap
    template<typename T>
    class HeapPriorityQueue : public ProjectAlpha::AbstractPriorityQueue<T> {
        // implementation details
    };

    // Concrete implementation of a hash set using a hash table
    template<typename T>
    class HashSet : public ProjectAlpha::AbstractHashSet<T> {
        // implementation details
    };
\
}


int main() {
    // test usage
    ProjectAlpha::LinkedListQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;

    // test usage
    ProjectAlpha:: LinkedListStack<int> stack;
    stack.push(1);
    stack.push(2);
    std::cout << stack.peek() << "\n";
    stack.pop();
    std::cout << stack.peek();
    return 0;
}
