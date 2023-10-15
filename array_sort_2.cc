// 补充头文件和其他起始成分
#include <iostream>
#include <algorithm>
using namespace std;

class array_sort
{
public:
    // 此处声明需要的成员函数
    void set_value();
    void sort_up();
    void display();
    void sort_down();

private:
    int n;
    int a[100];
};

// 下面定义成员函数
void array_sort::set_value()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        (cin >> a[i]).get();
    }
}

void array_sort::sort_up()
{
    sort(a, a + n, less<int>());
}

void array_sort::display()
{
    for (int i = 0; i < n - 1; i++)
    {
        cout << a[i] << ' ';
    }
    cout << a[n - 1] << endl;
}

void array_sort::sort_down()
{
    sort(a, a + n, greater<int>());
}
// 用main()函数测试，完成输入输出
int main()
{
    array_sort b1;
    // 输入数组元素个数及相应的数值
    b1.set_value();
    // 由小到大排序
    b1.sort_up();
    // 按序输出数组元素
    b1.display();
    // 由大到小排序
    b1.sort_down();
    // 按序输出数组元素
    b1.display();
    return 0;
}