#include <iostream>
#include <vector>
using namespace std;

class player1{
    private:
    int id;
    string name;
    float balance;
    bool turn;
    bool win;
    char input;
    vector<float> bet;
    string gameResult;

    public:
    player1() : balance(0.0), turn(false), win(false), input(' '), bet(0.0) {}

    float getBalance() const{
        return balance;
    }

    void setBalance(float balances){
        this->balance = balances;
    }

    void addBalance(float amount)
    {
        balance += amount;
    }

    void deductBalance(float amount)
    {
        balance -= amount;
    }

     void setGameResult(const string& result) {
        gameResult = result;
    }

    string getGameResult() const {
        return gameResult;
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

    void setName(string name){
        name = name;
    }

    // Get total bet amount
    float getTotalBetAmount()
    {
        double total = 0;
        for (int i = 0; i < bet.size(); i++)
        {
            total += bet[i];
        }
        return total;
    }

    float getBetBalance(float amount)
    {
        double totalBetAmount = getTotalBetAmount();
        return balance - totalBetAmount;
    }

    bool isWin(){
        return win;
    }

    bool isTurn(){
        return turn;
    }

    bool newisTurn(bool newTurn){
        this->turn = newTurn;
        return turn;
    }

    bool newWinner(bool newWIn){
        this->win = newWIn;
        return win;
    }

    char getInput(){
        return input;
    }

    void setInput(char inputs){
        this->input = inputs;
    }

    void setBet(float newBet){
        bet.push_back(newBet);
    }

};
