#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class KlaKlokPlayer
{
private:
    int id;
    string name;
    double balance;
    bool isTurn;
    bool isWinner;
    vector<int> inputValues;
    vector<double> betAmounts;

public:
    KlaKlokPlayer()
    {
        balance = 0;
        isWinner = false;
        isTurn = false;
    }

    int getId()
    {
        return id;
    }

    void setId(int newId)
    {
        id = newId;
    }

    string getName()
    {
        return name;
    }

    void setName(string newName)
    {
        name = newName;
    }

    double getBalance()
    {
        return balance;
    }

    void setBalance(double newBalance)
    {
        balance = newBalance;
    }

    void addBalance(double amount)
    {
        balance += amount;
    }

    void deductBalance(double amount)
    {
        balance -= amount;
    }

    bool getIsWinner()
    {
        return isWinner;
    }

    void setIsWinner(bool newIsWinner)
    {
        isWinner = newIsWinner;
    }

    bool getIsTurn()
    {
        return isTurn;
    }

    void setIsTurn(bool newIsTurn)
    {
        isTurn = newIsTurn;
    }

    // Get input values
    vector<int> getInputValues()
    {
        return inputValues;
    }

    // add input values
    void addInputValues(int value)
    {
        inputValues.push_back(value);
    }

    // Input exists
    bool inputExists(int value)
    {
        for (int i = 0; i < inputValues.size(); i++)
        {
            if (inputValues[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    // Clear input values
    void clearInputValues()
    {
        inputValues.clear();
    }

    // Get bet amounts
    vector<double> getBetAmounts()
    {
        return betAmounts;
    }

    // Add bet amounts
    void addBetAmounts(double amount)
    {
        betAmounts.push_back(amount);
    }

    // Clear bet amounts
    void clearBetAmounts()
    {
        betAmounts.clear();
    }

    // Get total bet amount
    double getTotalBetAmount()
    {
        double total = 0;
        for (int i = 0; i < betAmounts.size(); i++)
        {
            total += betAmounts[i];
        }
        return total;
    }

    // Get can bet amount
    double getCanBetAmount()
    {
        double totalBetAmount = getTotalBetAmount();
        return balance - totalBetAmount;
    }

    // Clear all player data
    void clearPlayerData()
    {
        balance = 0;
        isWinner = false;
        isTurn = false;
        inputValues.clear();
        betAmounts.clear();
        name = "";
        id = 0;
    }
};