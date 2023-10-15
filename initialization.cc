#include <iostream>
#include <utility>
using namespace std;

int main(int argc, char const *argv[])
{
    const int emmmmmm = 10;
    int &&ref = std::move(emmmmmm);
    ref = 5;
    cout << emmmmmm;
    return 0;
}