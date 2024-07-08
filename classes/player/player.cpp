#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct PlayerData
{
    int id;
    string name;
    double balance;
    int totalGames, wins, losses, draws;
};

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
        cout << left << setw(5) << "ID"
             << setw(15) << "Name"
             << setw(10) << "Balance"
             << setw(15) << "Total Games"
             << setw(10) << "Wins"
             << setw(10) << "Losses"
             << setw(10) << "Draws" << endl;

        cout << "============================================================================" << endl;

        for (int i = 0; i < players.size(); i++)
        {
            PlayerData player = players[i];
            cout << left << setw(5) << player.id
                 << setw(15) << player.name
                 << setw(10) << player.balance
                 << setw(15) << player.totalGames
                 << setw(10) << player.wins
                 << setw(10) << player.losses
                 << setw(10) << player.draws << endl;
        }

        cout << "============================================================================" << endl;
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

    // Check if name exists
    bool nameExists(const string &name) const
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i].name == name)
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
            cin >> name;

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
            else if (name.length() < 3 || name.length() > 15)
            {
                cout << "Player name must be between 3 and 15 characters. Please try again." << endl;
            }
            else
            {
                isValid = true;
            }
        }

        int id = players.size() + 1;
        double balance = 1000.0;
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
        cout << "Initializing players..." << endl;
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
};
