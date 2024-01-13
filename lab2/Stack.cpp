#include <iostream>
using namespace std;

template <typename T>
class Stack
{
    template <typename G>
    class Node
    {
    public:
        G data;
        Node<G> *pNext;

        Node() : data(G()), pNext(nullptr) {}
        Node(G data) : data(data), pNext(nullptr) {}
        Node(G data, Node<G> *pNext) : data(data), pNext(pNext) {}
    };

    Node<T> *head;

public:
    Stack();
    Stack(const Stack<T> &other);
    ~Stack();

    Stack<T>& operator=(const Stack<T> &other);

    bool isEmpty() const { return this->head == nullptr; }

    void push(T data);
    void pop();
    void deleteStack();

    T top() const;

    void tst()
    {
        Node<T> *tmp = head;
        while (tmp)
        {
            tmp = tmp->pNext;
        }
        
    }
};

template <typename T>
Stack<T>::Stack() { head = nullptr; }

template <typename T>
Stack<T>::~Stack() { deleteStack(); }

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    this->deleteStack();
    this = new Stack<T>(other);
    return *this;
}

template <typename T>
Stack<T>::Stack(const Stack<T> &other)
{
    if (other.isEmpty())
    {
        this->head = nullptr;
        return;
    }

    this->head = new Node<T>(other.head->data);
    Node<T> *curr = this->head;

    Node<T> *curr_other = other.head->pNext;
    while (curr_other != nullptr)
    {
        curr->pNext = new Node<T>(curr_other->data);
        curr = curr->pNext;
        curr_other = curr_other->pNext;
    }
}

template <typename T>
void Stack<T>::push(T data)
{
    head = new Node<T>(data, head);
}

template <typename T>
void Stack<T>::pop()
{
    if (isEmpty())
        return;

    Node<T> *tmpNode = head;
    head = head->pNext;
    delete tmpNode;
}

template <typename T>
void Stack<T>::deleteStack()
{
    while (!isEmpty())
    {
        pop();
    }

    head = nullptr;
}

template <typename T>
T Stack<T>::top() const
{
    if (!isEmpty())
        return head->data;

    return T();
}
