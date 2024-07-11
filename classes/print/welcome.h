#include <iostream>

using namespace std;

class Welcome
{
public:
    void welcome()
    {
        cout << "Lobby..." << endl;
    }

    void printWelcome()
    {
        cout << "============================================" << endl;
        cout << "Welcome to MiniGameHub by Team 1 - CS126" << endl;
        cout << "============================================" << endl;
    }

    void printExit()
    {
        cout << "============================================" << endl;
        cout << "Thank you for choosing MiniGameHub!" << endl;
        cout << "============================================" << endl
             << endl
             << endl;
    }
};
