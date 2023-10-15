#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    int length;
    (cin >> length).get();
    int array[length];
    string str{""};
    for (int i = 0; i < length; i++)
    {
        (cin >> array[i]).get();
        getline(cin, str);
    }
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << endl;
        cout << str;
    }

    return 0;
}