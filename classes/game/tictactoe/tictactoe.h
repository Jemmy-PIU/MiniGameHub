#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "../../player/player.h"
#include "../../print/styling.h"

using namespace std;

class TicTacToePlayer
{
private:
    int id;
    string name;
    char symbol;
    double balance;

public:
    TicTacToePlayer() : id(0), symbol(' '), balance(0) {}

    int getId() const { return id; }
    void setId(int newId) { id = newId; }

    string getName() const { return name; }
    void setName(const string &newName) { name = newName; }

    char getSymbol() const { return symbol; }
    void setSymbol(char newSymbol) { symbol = newSymbol; }

    double getBalance() const { return balance; }
    void setBalance(double newBalance) { balance = newBalance; }

    void deductBalance(double amount) { balance -= amount; }
    void addBalance(double amount) { balance += amount; }
};

class TicTacToeGame
{
private:
    int totalPlayers;
    vector<int> playerIDs;
    vector<string> playerNames;
    vector<double> playerStartingBalance;
    vector<TicTacToePlayer> players;
    vector<double> playerBets;

    char spaces[9];

public:
    TicTacToePrint styleMessage;

    TicTacToeGame()
    {
        clearGameData();
    }

    void setTotalPlayers()
    {
        totalPlayers = 2;
        cout << "======> Total players: " << totalPlayers << endl;
    }

    void updatePlayerStats(int playerID, string result)
    {
        Player player;
        player.updatePlayerGameStats(playerID, result);
        player.updateDataFile();
    }

    void setPlayerWhoPlaysByID()
    {
        Player player;
        for (int i = 0; i < totalPlayers; i++)
        {
            int playerID;
            bool validInput = false;
            while (!validInput)
            {
                cout << "Enter player " << i + 1 << " ID: ";
                cin >> playerID;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number. " << endl;
                }
                else
                {
                    PlayerData playerData = player.getPlayerById(playerID);
                    if (find(playerIDs.begin(), playerIDs.end(), playerData.id) != playerIDs.end())
                    {
                        cout << "Player " << playerData.name << " already registered! Please choose another ID!" << endl;
                    }
                    else if (playerData.id != 0)
                    {
                        cout << "Player " << playerData.name << " is ready to play!" << endl;
                        double startingBal;
                        bool validBalance = false;
                        while (!validBalance)
                        {
                            cout << "Enter starting balance for " << playerData.name << " (Wallet: $" << playerData.balance << "): ";
                            cin >> startingBal;
                            if (cin.fail() || startingBal < 1 || startingBal > playerData.balance)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid balance! Enter a value between 1 and " << playerData.balance << "." << endl;
                            }
                            else
                            {
                                validBalance = true;
                            }
                        }

                        double betAmount;
                        bool validBet = false;
                        while (!validBet)
                        {
                            cout << "Enter bet amount for " << playerData.name << ": ";
                            cin >> betAmount;
                            if (cin.fail() || betAmount < 1 || betAmount > startingBal)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid bet amount! Enter a value between 1 and " << startingBal << "." << endl;
                            }
                            else
                            {
                                validBet = true;
                            }
                        }
                        playerBets.push_back(betAmount);
                        playerIDs.push_back(playerData.id);
                        playerNames.push_back(playerData.name);
                        playerStartingBalance.push_back(startingBal);
                        validInput = true;
                    }
                    else
                    {
                        cout << "Player ID not found! Please enter a valid player ID." << endl;
                    }
                }
            }
        }
    }

    void setPlayers()
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            TicTacToePlayer player;
            player.setId(playerIDs[i]);
            player.setName(playerNames[i]);
            player.setSymbol(i == 0 ? 'X' : 'O');
            player.setBalance(playerStartingBalance[i]);
            players.push_back(player);
        }
    }

    void getAllPlayersBalance()
    {
        styleMessage.printHeading("All Players Balance");
        for (int i = 0; i < totalPlayers; i++)
        {
            cout << "#" << i + 1 << " " << players[i].getName() << "'s balance: $" << players[i].getBalance() << endl;
        }
        styleMessage.printFrame("All Players Balance");
    }

    void playGame()
    {
        styleMessage.headingMsg();

        setTotalPlayers();
        setPlayerWhoPlaysByID();

        setPlayers();
        getAllPlayersBalance();

        bool running = true;
        drawBoard();

        while (running)
        {
            for (int i = 0; i < totalPlayers; ++i)
            {
                playerMove(players[i].getSymbol());
                drawBoard();
                if (checkWinner(players[i].getSymbol(), players[(i + 1) % totalPlayers].getSymbol()))
                {
                    // Update player stats here
                    updatePlayerStats(players[i].getId(), "WIN");
                    updatePlayerStats(players[(i + 1) % totalPlayers].getId(), "LOSE");
                    running = false;
                    break;
                }
                else if (checkTie())
                {
                    // It's a draw, update stats for both players
                    updatePlayerStats(players[0].getId(), "DRAW");
                    updatePlayerStats(players[1].getId(), "DRAW");
                    running = false;
                    break;
                }
            }
        }

        styleMessage.exitMsg();
    }

    void drawBoard()
    {
        cout << '\n';
        cout << "     |     |     " << '\n';
        cout << "  " << spaces[0] << "  |  " << spaces[1] << "  |  " << spaces[2] << "  " << '\n';
        cout << "_____|_____|_____" << '\n';
        cout << "     |     |     " << '\n';
        cout << "  " << spaces[3] << "  |  " << spaces[4] << "  |  " << spaces[5] << "  " << '\n';
        cout << "_____|_____|_____" << '\n';
        cout << "     |     |     " << '\n';
        cout << "  " << spaces[6] << "  |  " << spaces[7] << "  |  " << spaces[8] << "  " << '\n';
        cout << "     |     |     " << '\n';
        cout << '\n';
    }

    void playerMove(char player)
    {
        int number;
        string playerName;

        // Find the player's name based on the symbol
        for (int i = 0; i < totalPlayers; ++i)
        {
            if (players[i].getSymbol() == player)
            {
                playerName = players[i].getName();
                break;
            }
        }

        do
        {
            cout << playerName << ", enter a spot to place a marker (1-9): ";
            cin >> number;
            number--;

            if (number < 0 || number > 8)
            {
                cout << "Invalid input! Please enter a number between 1 and 9." << endl;
            }
            else if (spaces[number] == ' ')
            {
                spaces[number] = player;
                break; // exit the loop when a valid spot is chosen
            }
            else
            {
                cout << "Spot already taken. Try again.\n";
            }
        } while (true); // continue looping until a valid move is made
    }

    bool checkWinner(char player, char opponent)
    {
        if ((spaces[0] != ' ') && (spaces[0] == spaces[1]) && (spaces[1] == spaces[2]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[3] != ' ') && (spaces[3] == spaces[4]) && (spaces[4] == spaces[5]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[6] != ' ') && (spaces[6] == spaces[7]) && (spaces[7] == spaces[8]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[0] != ' ') && (spaces[0] == spaces[3]) && (spaces[3] == spaces[6]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[1] != ' ') && (spaces[1] == spaces[4]) && (spaces[4] == spaces[7]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[2] != ' ') && (spaces[2] == spaces[5]) && (spaces[5] == spaces[8]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[0] != ' ') && (spaces[0] == spaces[4]) && (spaces[4] == spaces[8]))
        {
            updateBalances(player, opponent);
        }
        else if ((spaces[2] != ' ') && (spaces[2] == spaces[4]) && (spaces[4] == spaces[6]))
        {
            updateBalances(player, opponent);
        }
        else
        {
            return false;
        }
        return true;
    }

    void updateBalances(char winnerSymbol, char loserSymbol)
    {
        int winnerIndex = -1, loserIndex = -1;
        for (int i = 0; i < totalPlayers; ++i)
        {
            if (players[i].getSymbol() == winnerSymbol)
            {
                winnerIndex = i;
            }
            else if (players[i].getSymbol() == loserSymbol)
            {
                loserIndex = i;
            }
        }
        if (winnerIndex != -1 && loserIndex != -1)
        {
            double totalBet = playerBets[winnerIndex] + playerBets[loserIndex];
            players[winnerIndex].addBalance(totalBet);
            players[loserIndex].deductBalance(playerBets[loserIndex]);

            cout << players[winnerIndex].getName() << " wins and receives $" << totalBet << "!" << endl;
            cout << players[loserIndex].getName() << " loses $" << playerBets[loserIndex] << "." << endl;

            // Update the player's wallet in the system
            Player player;
            player.updatePlayerBalance(players[winnerIndex].getId(), playerBets[winnerIndex], totalBet);
            player.updatePlayerBalance(players[loserIndex].getId(), 0, -playerBets[loserIndex]);

            // Update the player's game stats
            updatePlayerStats(players[winnerIndex].getId(), "WIN");
            updatePlayerStats(players[loserIndex].getId(), "LOSE");

            // Save the updated balance to the file
            player.updateDataFile();
        }
    }

    bool checkTie()
    {
        for (int i = 0; i < 9; i++)
        {
            if (spaces[i] == ' ')
            {
                return false;
            }
        }
        cout << "It's a tie!\n";

        // Update player stats here
        updatePlayerStats(players[0].getId(), "DRAW");
        updatePlayerStats(players[1].getId(), "DRAW");

        return true;
    }

    void clearGameData()
    {
        totalPlayers = 0;
        playerIDs.clear();
        playerNames.clear();
        playerStartingBalance.clear();
        players.clear();
        for (int i = 0; i < 9; ++i)
        {
            spaces[i] = ' '; // Initialize spaces to empty
        }
    }
};
