#include <stdexcept>

template <typename T>
struct Node
{
    T data;

    Node<T> *prev;
    Node<T> *next;

    Node() : data(T()), prev(nullptr), next(nullptr) {}
    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
    Node(T data, Node<T>* prev) : data(data), prev(prev), next(nullptr) {}
    Node(T data, Node<T>* prev, Node<T>* next) : data(data), prev(prev), next(next) {}

    Node(Node<T>& node) : data(node.data), prev(node.prev), next(node.next) {}
};

template <typename T>
class ListIterator
{
    Node<T>* curr;

public:

    ListIterator() : curr(nullptr) {}
    ListIterator(Node<T>* node) : curr(node) {}

    ListIterator<T> &operator=(Node<T>* node) { curr = node; }

    T &operator*() { return curr->data; }

    ListIterator<T> &operator++()
    {
        if (curr != nullptr)
            curr = curr->next;

        return *this;
    }

    ListIterator<T> operator++(int)
    {
        ListIterator it = *this;
        ++(*this);
        return it;
    };

    ListIterator<T> &operator--()
    {
        if (curr != nullptr)
            curr = curr->prev;

        return *this;
    }

    ListIterator<T> operator--(int)
    {
        ListIterator it = *this;
        --(*this);
        return it;
    };

    bool operator==(const ListIterator<T> &it) { return this->curr == it.curr; }
    bool operator!=(const ListIterator<T> &it) { return this->curr != it.curr; }

};


template <typename T>
class List
{
private:
    Node<T> *head;
    Node<T> *tail;

    int size;

public:
    // using Iterator = ListIterator<T>;

public:

    List() : head(nullptr), tail(nullptr), size(0) {}

    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return size; }

    void pushFront(T data);
    void pushBack(T data);

    void popFront();
    void popBack();

    void insertAt(T data, int index);
    void removeAt(int index);

    T &at(int index);

    void destroy();

    ListIterator<T> begin() { return ListIterator<T>(head); }
    ListIterator<T> end() { return ListIterator<T>(nullptr); }

};


template <typename T>
void List<T>::pushFront(T data)
{
    head = new Node<T>(data, nullptr, head);

    if (tail == nullptr)
    {
        tail = head;
    }
    else
    {
        head->next->prev = head;
    }

    size++;
}


template <typename T>
void List<T>::pushBack(T data)
{
    tail = new Node<T>(data, tail, nullptr);

    if (head == nullptr)
    {
        head = tail;
    }
    else
    {
        tail->prev->next = tail;
    }

    size++;
}

template <typename T>
void List<T>::popFront()
{
    if (isEmpty()) throw std::invalid_argument("Can't remove from an empty list.");

    Node<T>* tmp = head;
    head = head->next;

    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    else
    {
        tail == nullptr;
    }

    delete tmp;
    size--;
}

template <typename T>
void List<T>::popBack()
{
    if (isEmpty()) throw std::invalid_argument("Can't remove from an empty list.");

    Node<T>* tmp = tail;
    tail = tail->prev;

    if (tail != nullptr)
    {
        tail->next = nullptr;
    }
    else
    {
        head = nullptr;
    }

    delete tmp;
    size--;
}

template <typename T>
void List<T>::insertAt(T data, int index)
{
    if (index < 0 || index > this->size) throw std::invalid_argument("List index out of range.");

    if (index == 0)
    {
        this->pushFront(data);
        return;
    }
    if (index == this->size)
    {
        this->pushBack(data);
        return;
    }

    if (index < this->size / 2)
    {
        Node<T> *current = this->head;

        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        current->next = new Node<T>(data, current, current->next);
        current->next->next->prev = current->next;
    }
    else
    {
        Node<T> *current = this->tail;

        for (int i = size - 1; i > index; i--)
        {
            current = current->prev;
        }

        current->prev = new Node<T>(data, current, current->prev);
        current->prev->prev->next = current->prev; 
    }

    this->size++;
}


template <typename T>
void List<T>::removeAt(int index)
{
    if (index < 0 || index >= size) throw std::invalid_argument("List index out of range.");

    if (index == 0)
    {
        popFront();
        return;
    }
    if (index == size - 1)
    {
        popBack();
        return;
    }

    if (index <= size / 2)
    {
        Node<T> *curr = head;

        for (int i = 0; i < index - 1; i++)
        {
            curr = curr->next;
        }

        Node<T> *toDelete = curr->next;

        curr->next = toDelete->next;
        curr->next->prev = curr;

        delete toDelete;
    }
    else
    {
        Node<T> *curr = tail;

        for (int i = size - 1; i > index - 1; i--)
        {
            curr = curr->prev;
        }

        Node<T> *toDelete = curr->next;

        curr->next = curr->next->next;
        curr->next->prev = curr;

        delete toDelete;
    }

    size--;
}

template <typename T>
T &List<T>::at(int index)
{
    Node<T> *curr = this->head;
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }

    return curr->data;
}

template <typename T>
void List<T>::destroy()
{
    while (head != nullptr)
    {
        tail = head;
        delete head;
        head = tail->next;
    }

    head = nullptr;
    tail = nullptr;

    size = 0;
}
