#include <iostream>
#include "2LinkedList.cpp"

using namespace std;

class Polynomial
{
private:
    List<double> poly;

public:
    int getPow() { return poly.getSize() - 1; }

    void add(double val)
    {
        poly.pushBack(val);
    }

    double &at(int index) { return poly.at(index); }
    double &operator[](int index) { return at(index); }
};

List<double> restorePoly(List<double> &roots)
{
    List<double> poly;

    ListIterator<double> it = roots.begin();
    poly.pushBack(-(*it));
    // poly.pushBack(1);
    ++it;

    while (it != roots.end())
    {
        double new_coeff = -(*it);

        // *poly.begin() *= new_coeff;

        int prev_coeff = 0;

        poly.pushBack(1);
        for (ListIterator<double> it_l = poly.begin(); it_l != poly.end(); ++it_l)
        {
            int tmp = *it_l;
            *it_l = *it_l * new_coeff + prev_coeff;
            prev_coeff = tmp;
        }

        ++it;
    }

    poly.pushBack(1);

    return poly;
}

template <typename T>
void printList(List<T> list)
{
    for (ListIterator<double> it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void printPoly(List<double> poly)
{
    if (poly.isEmpty())
        return;

    ListIterator<double> it = poly.begin();

    cout << *it;
    ++it;

    int i = 1;
    while (it != poly.end())
    {
        double coeff = *it;

        if (coeff == 1)
            cout << "+x^" << noshowpos << i;
        else if (coeff == -1)
            cout << "-x^" << noshowpos << i;
        else if (coeff != 0)
            cout << showpos << coeff << "x^" << noshowpos << i;

        ++i;
        ++it;
    }

    cout << noshowpos << endl;
}

int main()
{
    List<double> roots;

    roots.pushBack(4);
    roots.pushBack(-2);
    roots.pushBack(6);
    roots.pushBack(-20);

    List<double> poly = restorePoly(roots);

    printPoly(poly);


    return 0;
}