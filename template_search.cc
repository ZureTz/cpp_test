#include <iostream>
#include <vector>
using namespace std;

template <typename T>
int Search(T item, vector<T> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i) == item)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    vector<int> intArray{
        2,
        3,
        4,
        5,
        6,
        45645,
        234,
        2345,
    };

    vector<double> doubleArray{
        2.5,
        3.24,
        43.23,
        234.12123,
        3452,
    };

    cout << Search(3, intArray) << endl
         << Search(3.25, doubleArray);

    return 0;
}