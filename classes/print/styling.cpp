#include <iostream>

using namespace std;

class Styling
{
public:
    void styling()
    {
        cout << "Styling..." << endl;
    }

    void printHeading(string msg)
    {
        cout << endl
             << "====[ " << msg << " ]====" << endl;
    }

    void printFooter(string msg)
    {
        int msgLength = msg.length();
        string msgFooter = "======" + string(msgLength, '=') + "======";
        cout
            << msgFooter << endl
            << endl;
    }
};
