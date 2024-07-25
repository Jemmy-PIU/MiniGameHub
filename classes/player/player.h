#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#pragma once
#include "../../struct/struct.h"

using namespace std;

class Players
{
protected:
    vector<PlayerData> players;

public:
    Players()
    {
        vector<PlayerData> players = this->players;
    }

    // Display players list in table format
    void listPlayers() const
    {
        cout << endl
             << "=================================================================================" << endl;

        cout << left << setw(5) << "ID"
             << setw(15) << "Name"
             << setw(20) << "Balance"
             << setw(15) << "Total Games"
             << setw(10) << "Wins"
             << setw(10) << "Losses"
             << setw(10) << "Draws" << endl;

        cout << "=================================================================================" << endl;

        for (int i = 0; i < players.size(); i++)
        {
            PlayerData player = players[i];

            // Add $ sign to balance only 2 decimal points
            string pbalance = "$" + to_string(player.balance).substr(0, to_string(player.balance).find(".") + 3);
            cout << left << setw(5) << player.id
                 << setw(15) << player.name
                 << setw(20) << pbalance
                 << setw(15) << player.totalGames
                 << setw(10) << player.wins
                 << setw(10) << player.losses
                 << setw(10) << player.draws << endl;
        }

        cout << "=================================================================================" << endl;
    }

    // Get player by ID
    PlayerData getPlayerById(int id) const
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].id == id)
            {
                return players[i];
            }
        }

        return PlayerData();
    }

    // Get player position by ID using pointer
    PlayerData *getPlayerByIdPointer(int id)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].id == id)
            {
                return &players[i];
            }
        }

        return nullptr;
    }

    // Check if name exists
    bool nameExists(const string &name) const
    {
        for (int i = 0; i < players.size(); i++)
        {
            // Convert name to lowercase for case-insensitive comparison
            string playerName = players[i].name;
            transform(playerName.begin(), playerName.end(), playerName.begin(), ::tolower);

            string inputName = name;
            transform(inputName.begin(), inputName.end(), inputName.begin(), ::tolower);

            if (playerName == inputName)
            {
                return true;
            }
        }

        return false;
    }

    // Register a new player
    void registerPlayer()
    {
        cout << "========== Register A New Player ==========" << endl;
        string name;
        bool isValid = false;
        while (!isValid)
        {
            cout << "Enter player name: ";
            getline(cin, name);

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a valid player name." << endl;
            }
            else if (nameExists(name))
            {
                cout << "Player name already exists. Please try again." << endl;
            }
            else if (name.length() < 3 || name.length() > 20)
            {
                cout << "Player name must be between 3 and 20 characters. Please try again." << endl;
            }
            else
            {
                isValid = true;
            }
        }

        int id = players.size() + 1;
        double balance = 2000.0;
        int totalGames = 0, wins = 0, losses = 0, draws = 0;

        PlayerData player = {id, name, balance, totalGames, wins, losses, draws};
        players.push_back(player);

        fstream file("./config/data.ini", ios::in | ios::out | ios::ate);

        // Get the last position of the file
        streampos endPosition = file.tellg();

        // Trim newline character if it exists
        file.seekg(-1, ios_base::end);
        char ch;
        file.get(ch);
        if (ch == '\n')
        {
            file.seekg(-1, ios_base::cur);
            endPosition = file.tellg();
        }

        // Move back to the end of the file for appending
        file.seekp(endPosition);

        if (endPosition != 0)
        {
            file << endl;
        }

        // Append new data
        file << id << "," << name << "," << balance << "," << totalGames << "," << wins << "," << losses << "," << draws;

        file.close();

        cout << "Player " << name << " has been registered successfully!" << endl;
    }

    // Find player by ID
    void findPlayerByID()
    {
        int id;
        bool isValid = false;
        cout << "========== Find Player By ID ==========" << endl;

        while (!isValid)
        {

            cout << "Enter player ID: ";
            cin >> id;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a valid player ID or enter 0 to exit." << endl;
            }
            else if (id < 0 || id > players.size())
            {
                cout << "Player ID must be between 1 and " << players.size() << ". Please try again or enter 0 to exit." << endl;
            }
            else if (id == 0)
            {
                isValid = true;
                break;
            }
            else
            {
                PlayerData player = getPlayerById(id);
                if (player.id != 0)
                {
                    cout << "==========[ Player's Information ] ==========" << endl;
                    cout << "ID: " << player.id << endl;
                    cout << "Name: " << player.name << endl;
                    cout << "Balance: $" << player.balance << endl;
                    cout << "Total Games: " << player.totalGames << endl;
                    cout << "Wins: " << player.wins << endl;
                    cout << "Losses: " << player.losses << endl;
                    cout << "Draws: " << player.draws << endl;
                    cout << "=============================================" << endl;
                }
                else
                {
                    cout << "Player not found. Please try again." << endl;
                }
            }
        }
    }

    // Find player by name
    void findPlayerByName()
    {
        string name;
        bool isValid = false;
        cout << "========== Find Player By Name ==========" << endl;

        while (!isValid)
        {
            cout << "Enter player name: ";
            getline(cin, name);

            // Check if input is 0
            if (name == "0")
            {
                isValid = true;
                break;
            }

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a valid player name or enter 0 to exit." << endl;
            }
            else if (!nameExists(name))
            {
                cout << "Player name not found. Please try again or enter 0 to exit." << endl;
            }
            else
            {
                for (int i = 0; i < players.size(); i++)
                {
                    // Convert name to lowercase for case-insensitive comparison
                    string playerName = players[i].name;
                    transform(playerName.begin(), playerName.end(), playerName.begin(), ::tolower);

                    string inputName = name;
                    transform(inputName.begin(), inputName.end(), inputName.begin(), ::tolower);

                    if (playerName == inputName)
                    {
                        PlayerData player = players[i];
                        cout << "==========[ Player's Information ] ==========" << endl;
                        cout << "ID: " << player.id << endl;
                        cout << "Name: " << player.name << endl;
                        cout << "Balance: $" << player.balance << endl;
                        cout << "Total Games: " << player.totalGames << endl;
                        cout << "Wins: " << player.wins << endl;
                        cout << "Losses: " << player.losses << endl;
                        cout << "Draws: " << player.draws << endl;
                        cout << "=============================================" << endl;
                        break;
                    }
                }
            }
        }
    }

    // Update data.ini file
    void updateDataFile()
    {
        // Update data.ini file
        fstream file("./config/data.ini", ios::out | ios::trunc);
        file << "# Player ID, Name, Balance, Total Games, Wins, Losses, Draws" << endl;
        for (int i = 0; i < players.size(); i++)
        {
            PlayerData player = players[i];
            file << player.id << "," << player.name << "," << player.balance << "," << player.totalGames << "," << player.wins << "," << player.losses << "," << player.draws << endl;
        }

        file.close();
    }

    // Transfer balance from one player to another
    void transferBalance()
    {
        int senderId, receiverId;
        double amount;
        bool inputtingSender = true;
        bool inputtingReceiver = false;
        bool validInputs = false;
        PlayerData senderData, receiverData;

        cout << "========== Transfer Balance ==========" << endl;

        while (inputtingSender)
        {
            cout << "Enter sender ID: ";
            cin >> senderId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a valid player ID or enter 0 to exit." << endl;
            }
            else if (senderId < 0 || senderId > players.size())
            {
                cout << "Player ID must be between 1 and " << players.size() << ". Please try again or enter 0 to exit." << endl;
            }
            else if (senderId == 0)
            {
                inputtingSender = false;
                break;
            }
            else
            {
                PlayerData sender = getPlayerById(senderId);
                if (sender.id != 0)
                {
                    if (sender.balance == 0)
                    {
                        cout << "Sender has no balance to transfer. Please try again." << endl;
                        continue;
                    }

                    senderData = sender;
                    inputtingSender = false;
                    inputtingReceiver = true;

                    cout << "Sender: " << senderData.name << " | Balance: $" << senderData.balance << endl;
                }
                else
                {
                    cout << "Sender not found. Please try again." << endl;
                }
            }
        }

        // Sender found, now input receiver
        while (inputtingReceiver)
        {
            cout << "Enter receiver ID: ";
            cin >> receiverId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a valid player ID or enter 0 to exit." << endl;
            }
            else if (receiverId < 0 || receiverId > players.size())
            {
                cout << "Player ID must be between 1 and " << players.size() << ". Please try again or enter 0 to exit." << endl;
            }
            else if (receiverId == senderId)
            {
                cout << "Sender and receiver cannot be the same player. Please try again or enter 0 to exit." << endl;
            }
            else if (receiverId == 0)
            {
                inputtingReceiver = false;
                break;
            }
            else
            {
                PlayerData receiver = getPlayerById(receiverId);
                if (receiver.id != 0)
                {
                    receiverData = receiver;
                    inputtingReceiver = false;
                    validInputs = true;
                    cout << "Receiver: " << receiverData.name << " | Balance: $" << receiverData.balance << endl;
                }
                else
                {
                    cout << "Receiver not found. Please try again." << endl;
                }
            }
        }

        // Transfer balance from sender to receiver
        if (validInputs)
        {
            // Transfer Information
            cout << endl
                 << "========== Transfer Information ==========" << endl;
            cout << "Sender: " << senderData.name << " | Balance: $" << senderData.balance << endl;
            cout << "Receiver: " << receiverData.name << " | Balance: $" << receiverData.balance << endl;
            cout << "==========================================" << endl;

            bool isValid = false;
            while (!isValid)
            {
                cout << "Enter amount to transfer: $";
                cin >> amount;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter a valid amount to transfer." << endl;
                }
                else if (amount <= 0 || amount > senderData.balance)
                {
                    cout << "Amount must be greater than 0 and less than or equal to sender's balance. Please try again." << endl;
                }
                else
                {
                    // Deduct balance from sender
                    senderData.balance -= amount;

                    // Add balance to receiver
                    receiverData.balance += amount;

                    // Update players vector
                    for (int i = 0; i < players.size(); i++)
                    {
                        if (players[i].id == senderData.id)
                        {
                            players[i] = senderData;
                        }
                        else if (players[i].id == receiverData.id)
                        {
                            players[i] = receiverData;
                        }
                    }

                    // Update data.ini file
                    updateDataFile();
                    cout << "Transfer successful!" << endl;

                    isValid = true;
                }
            }
        }
    }

    // Update player balance after game
    void updatePlayerBalance(int playerID, double initialAmount, double finalAmount)
    {
        PlayerData *thatPlayer = getPlayerByIdPointer(playerID);

        // using pointer to update player balance
        if (thatPlayer != nullptr)
        {
            thatPlayer->balance = thatPlayer->balance + finalAmount - initialAmount;
        }
    }

    // Update player game stats win, lose or draw
    void updatePlayerGameStats(int playerID, string status)
    {
        PlayerData *thatPlayer = getPlayerByIdPointer(playerID);
        if (status == "WIN")
        {
            thatPlayer->wins++;
        }
        else if (status == "LOSE")
        {
            thatPlayer->losses++;
        }
        else
        {
            thatPlayer->draws++;
        }

        // Add total games
        thatPlayer->totalGames++;
    }
};

class Player : public Players
{
protected:
    int id;
    string name;
    double balance;
    int totalGames, wins, losses, draws;

public:
    Player()
    {
        string filename = "./config/data.ini";
        readPlayersFromFile(filename);
    }

    void readPlayersFromFile(const string &filename)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            // Skip comments and empty lines
            if (line.empty() || line[0] == '#')
                continue;

            // Parse player data
            stringstream ss(line);
            int id, totalGames, wins, losses, draws;
            double balance;
            string name;

            // Read the CSV values
            ss >> id;
            ss.ignore(); // Skip comma
            getline(ss, name, ',');
            ss >> balance;
            ss.ignore(); // Skip comma
            ss >> totalGames;
            ss.ignore(); // Skip comma
            ss >> wins;
            ss.ignore(); // Skip comma
            ss >> losses;
            ss.ignore(); // Skip comma
            ss >> draws;

            this->id = id;
            this->name = name;
            this->balance = balance;
            this->totalGames = totalGames;
            this->wins = wins;
            this->losses = losses;
            this->draws = draws;

            PlayerData player = {id, name, balance, totalGames, wins, losses, draws};
            this->players.push_back(player);
        }

        file.close();
    }

    int getPlayerId() const
    {
        return id;
    }

    string getPlayerName() const
    {
        return name;
    }

    double getPlayerBalance() const
    {
        return balance;
    }

    int getPlayerTotalGames() const
    {
        return totalGames;
    }

    int getPlayerWins() const
    {
        return wins;
    }

    int getPlayerLosses() const
    {
        return losses;
    }

    int getPlayerDraws() const
    {
        return draws;
    }

    void setPlayerName(string name)
    {
        this->name = name;
    }

    void setPlayerBalance(double balance)
    {
        this->balance = balance;
    }

    void setPlayerTotalGames(int totalGames)
    {
        this->totalGames = totalGames;
    }

    void setPlayerWins(int wins)
    {
        this->wins = wins;
    }

    void setPlayerLosses(int losses)
    {
        this->losses = losses;
    }

    void setPlayerDraws(int draws)
    {
        this->draws = draws;
    }
};
