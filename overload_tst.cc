#include <iostream>
using namespace std;

template <typename number>
number add(number (&a)[])
{
    return a[1] + a[2];
}

int main(int argc, char const *argv[])
{
    int a[]{3, 4, 5, 6, 7, 8, 9, 10};
    cout << add(a) << endl;
    return 0;
}
