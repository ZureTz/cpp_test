#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> array_original;
    int length;
    (cin >> length).get();

    array_original.resize(length);
    for (auto item = array_original.begin(); item < array_original.end(); item++)
    {
        cin >> *item;
    }

    vector<int> array_Sorted = array_original;
    sort(array_Sorted.begin(), array_Sorted.end(), less<int>());

    vector<int> array_invSorted = array_original;
    sort(array_invSorted.begin(), array_invSorted.end(), greater<int>());

    for (auto item = array_Sorted.begin(); item < array_Sorted.end() - 1; item++)
    {
        cout << *item << ' ';
    }
    cout << *(array_Sorted.end() - 1)                           << endl;
            /* array_Sorted.at(array_Sorted.size() - 1) */

    for (auto item = array_invSorted.begin(); item < array_invSorted.end() - 1; item++)
    {
        cout << *item << ' ';
    }
    cout << *(array_invSorted.end() - 1)                         << endl;
            /* array_invSorted.at(array_invSorted.size() - 1) */

    return 0;
}