#include <iostream>
#include <string>
#include "Stack.cpp"
using namespace std;

void fillNames(Stack<string> &books)
{
    books.push("Bloodborne");
    books.push("Divergent");
    books.push("The fourth wall.");
    books.push("Discrete math");
    books.push("Howard the Duck");

    // books.tst();

}

template <typename T>
void printStack(Stack<T> st)
{
    while(!st.isEmpty())
    {
        cout << st.top() << endl;
        st.pop();
    }
}

template <typename T>
Stack<T> sortStack(Stack<T> &st)
{
    Stack<T> sorted;
    T tmp;

    while(!st.isEmpty())
    {
        tmp = st.top();
        st.pop();

        while (!sorted.isEmpty() && sorted.top().size() > tmp.size())
        {
            st.push(sorted.top());
            sorted.pop();
        }
        sorted.push(tmp);
    }

    return sorted;
}

int main()
{
    Stack<string> books;
    fillNames(books);

    printStack<string>(books);
    cout << endl << "Sorted:" << endl << endl;
    printStack<string>(sortStack<string>(books));

    return 0;
}