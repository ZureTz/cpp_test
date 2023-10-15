#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    auto a = 133;
    auto ptr = &a;
    *ptr = 23;
    cout << a << '\t' << sizeof a;

    return 0;
}