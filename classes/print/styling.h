#include <iostream>

using namespace std;

class Styling
{
public:
    void styling()
    {
        cout << "Styling......" << endl;
    }

    void printHeading(string msg)
    {
        cout << "=========[ " << msg << " ]=========" << endl;
    }

    void printFrame(string msg)
    {
        int msgLength = msg.length();
        string msgFooter = "===========" + string(msgLength, '=') + "===========";
        cout
            << msgFooter << endl;
    }

    void printGameTitle(string msg)
    {
        printFrame(msg);
        printHeading(msg);
        printFrame(msg);
    }
};

class KlaKlokPrint : public Styling
{
public:
    void headingMsg()
    {
        printGameTitle("KlaKlok V1");
    }

    void randomDiceMsg(vector<int> diceValues)
    {
        printHeading("KlaKlok-Dices Rolled Values");

        for (int i = 0; i < diceValues.size(); i++)
        {
            cout << "=" + string(18, ' ') << diceValues[i] << string(18, ' ') + "=" << endl;
        }

        printFrame("KlaKlok-Dices Rolled Values");
    }

    void exitMsg()
    {
        printFrame("Exiting KlaKlok V1");
        printHeading("Exiting KlaKlok V1");
        printFrame("Exiting KlaKlok V1");
    }
};

class TicTacToePrint : public Styling
{
public:
    void headingMsg()
    {
        printGameTitle("Tic Tac Toe V1");
    }
};