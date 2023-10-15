#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    cout << string(R"qwpwq(printf("Hello, world!!!");)qwpwq").at(6);

    return 0;
}
