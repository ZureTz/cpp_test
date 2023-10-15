#include <iostream>
#include <vector>
using namespace std;


class A{
    int a;
};

class B:A{
    float b;
};

int main(int argc, char const *argv[])
{
    vector<int> array{
        1,
        2,
        3,
        4,
        5,
    };

    for (int i = 0; i < array.size(); i++)
    {
        cout << array.at(i) << " ";
    }

    return 0;
}