#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;

class io
{
public:
    void processData();
};

int main(int argc, char const *argv[])
{
    io instace;
    instace.processData();
    return 0;
}

void io::processData()
{
    std::string str;
    const std::string rep1 = "\\textbf{";
    const std::string rep2 = "}";
    std::getline(cin, str, '%');

    for (int pos1 = 0; pos1 < str.length(); pos1++)
    {
        if (str.at(pos1) == '`')
        {
            for (int pos2 = pos1 + 1; pos2 < str.length(); pos2++)
            {
                if (str.at(pos2) == '`')
                {
                    str.replace(pos1, 1, rep1);
                    pos1 += rep1.length() - 1;
                    pos2 += rep1.length() - 1;
                    str.replace(pos2, 1, rep2);
                    break;
                }
            }
        }
    }

    const std::string rep3 = "\\_";
    for (int i = 0; i < str.length(); i++)
    {
        if (str.at(i) == '_')
        {
            str.replace(i, 1, rep3);
            i += rep3.length() - 1;
        }
    }

    cout << str;
}