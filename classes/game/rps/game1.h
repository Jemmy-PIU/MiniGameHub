#include <iostream>
#include <vector>
#include <fstream>
#include "player1.h"
#include "../../player/player.h"
using namespace std;

class Game1
{
private:
    int total;
    vector<float> playerMoney;
    vector<string> playerNames;
    float startingBalance;
    vector<player1> players;
    vector<int> playerIDs;
    vector<string> gameHistory;
    int recordCounter;

public:
    Game1() : total(0), startingBalance(0.0), recordCounter(1)
    {
        srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
        // Initialize the recordCounter by reading the file
        ifstream inFile("record.txt");
        string line;
        while (std::getline(inFile, line))
        {
            // Assuming the format "Game History X:" is consistent
            if (line.find("Game History") != string::npos)
            {
                // Find the last recorded game number
                int num = std::stoi(line.substr(13, line.find(":") - 13));
                if (num >= recordCounter)
                {
                    recordCounter = num + 1;
                }
            }
        }
        inFile.close();
    }

    vector<float> getBalanceSummary() const
    {
        vector<float> balances;
        for (const player1 &player : players)
        {
            balances.push_back(player.getBalance());
        }
        return balances;
    }

    void setTotalPlayers()
    {
        int number;
        bool input = false;
        while (!input)
        {
            cout << "Enter the number of players: ";
            cin >> number;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "Invalid input! Please enter a number." << endl;
            }
            else if (number > 2 || number < 1)
            {
                cout << "Number of player should be between 2" << endl;
            }
            else
            {
                input = true;
            }
        }
        this->total = number;
    }

    int getTotalPlayers()
    {
        return total;
    };

    vector<player1> getPlayers()
    {
        return this->players;
    };

    // Set starting balance for each player
    void startBalance(const PlayerData &playerDat)
    {
        // Set starting balance for selected player
        double startingBal;
        bool validInput = false;
        while (!validInput)
        {
            cout << "Enter starting balance for " << playerDat.name << " (Wallet: $" << playerDat.balance << "): ";
            cin >> startingBal;

            // Check if input is valid
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
            }
            else if (startingBal < 1 || startingBal > playerDat.balance)
            {
                cout << "Starting balance should be between 1 and " << playerDat.balance << "!" << endl;
            }
            else
            {
                validInput = true;
            }
        }
        this->playerMoney.push_back(startingBal);
    };

    void setPlayers()
    {
        for (int i = 0; i < total; i++)
        {
            player1 newplayer;
            newplayer.setId(playerIDs[i]);
            newplayer.setName(playerNames[i]);
            newplayer.setBalance(playerMoney[i]);
            players.push_back(newplayer);
        }
    }

    // Print players balance
    void getAllPlayersBalance()
    {
        // styleMessage.printHeading("All Players Balance");
        for (int i = 0; i < total; i++)
        {
            cout << "#" << i + 1 << " " << playerNames[i] << "'s balance: $" << this->players[i].getBalance() << endl;
        }
        // styleMessage.printFrame("All Players Balance");
    }

    // Get starting balance for each player
    vector<float> getPlayerStartingBalance()
    {
        return playerMoney;
    };

    void setPlayerWhoPlaysByID()
    {
        Player player;
        for (int i = 0; i < total; i++)
        {
            int playerID;
            bool validInput = false;
            while (!validInput)
            {
                cout << "Enter player " << i + 1 << " ID: ";
                cin >> playerID;

                // Check if input is valid
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number. " << endl;
                }
                else
                {
                    PlayerData playerData = player.getPlayerById(playerID);

                    // Check if player ID already exists
                    if (find(playerIDs.begin(), playerIDs.end(), playerData.id) != playerIDs.end())
                    {

                        cout << "Player " << playerData.name << " already registered! Please choose another ID!" << endl;
                    }
                    else if (playerData.id != 0)
                    {
                        // Check if player has enough balance
                        if (playerData.balance <= 0)
                        {
                            cout << "Player " << playerData.name << " does not have enough balance to play! Please choose another ID!" << endl;
                        }
                        else
                        {
                            cout << "Player " << playerData.name << " is ready to play!" << endl;
                            startBalance(playerData);
                            playerIDs.push_back(playerData.id);
                            playerNames.push_back(playerData.name);
                            validInput = true;
                        }
                    }
                    else
                    {
                        cout << "Player ID not found! Please enter a valid player ID." << endl;
                    }
                }
            }
        }
    }

    void setLow()
    {
        double avrBal = 0;
        for (int i = 0; i < playerMoney.size(); i++)
        {
            avrBal += playerMoney[i];
        }

        this->startingBalance = avrBal / playerMoney.size();
    };

    char getBotchoice()
    {
        int choice = rand() % 3 + 1;
        if (choice == 1)
            return 'r';
        if (choice == 2)
            return 'p';
        return 's';
    }

    string determineWinner(char playerInput, char botChoice)
    {
        if ((playerInput == 'r' && botChoice == 'r') ||
            (playerInput == 'p' && botChoice == 'p') ||
            (playerInput == 's' && botChoice == 's'))
        {
            return "Draw";
        }
        else if ((playerInput == 'r' && botChoice == 's') ||
                 (playerInput == 'p' && botChoice == 'r') ||
                 (playerInput == 's' && botChoice == 'p'))
        {
            return "Player";
        }
        else if ((playerInput == 's' && botChoice == 'r') ||
                 (playerInput == 'r' && botChoice == 'p') ||
                 (playerInput == 'p' && botChoice == 's'))
        {
            return "Bot";
        }
        return "invalid";
    }

    void playerTurn()
    {
        string gameRecord;
        bool gameEnded = false;
        // Check if any player has a balance of 0
        for (const auto &num : players)
        {
            if (num.getBalance() <= 0)
            {
                gameEnded = true;
                break;
            }
        }

        if (gameEnded)
        {
            cout << "One of the players has run out of balance. Ending the game." << endl;
            return;
        }

        for (int i = 0; i < total; i++)
        {
            player1 &current = players[i];
            cout << endl
                 << "=====> Player " << i + 1 << "'s turn <=====" << endl;
            current.newisTurn(true);
            while (current.isTurn() == true)
            {
                char input;
                bool valid = false;
                while (!valid)
                {
                    // get input r, p, s
                    cout << "Enter the letter (r : rock, p : paper, s : scissor): ";
                    cin >> input;
                    if (input == 'r' || input == 'p' || input == 's' || input == 'R' || input == 'S' || input == 'P')
                    {
                        valid = true;
                    }
                    else
                    {
                        cout << "invalid input! please enter the letter (r , p , s) " << endl;
                    }
                }
                current.setInput(input);

                // set the bet
                float cash;
                bool VALID = false;
                while (!VALID)
                {
                    cout << "Enter the bet amount: ";
                    cin >> cash;
                    if (cin.fail() || cash <= 0)
                    {
                        cin.clear();
                        cin.ignore();
                        cout << "invalid input! please enter the bet amount again. (larger than 0) " << endl;
                    }
                    else if (cash > current.getBalance())
                    {
                        cout << "Input must be lower or euqal to the balance" << endl;
                    }
                    else
                    {
                        VALID = true;
                    }
                }
                current.setBet(cash);

                // bot turn
                char bot = getBotchoice();

                // determine winner
                string winner = determineWinner(current.getInput(), bot);

                // Record the result in the player object
                current.setGameResult(winner);

                // Record game history for the current player
                gameRecord += "\n: Player " + to_string(i + 1) + ": " + current.getInput() +
                              "\n| Bot: " + bot + "\n| Result: " + winner; // to_string is to conver the number to the string to connect with other string
                cout << endl;
                cout << "-----------------------------" << endl;
                cout << "Player " << i + 1 << " : " << current.getInput() << endl;
                cout << "Bot choose : " << bot << endl;
                if (winner == "Player")
                {
                    cout << "Player " << i + 1 << " wins this round! " << endl;
                    cout << "=============================" << endl;
                    current.addBalance(cash);
                }
                else if (winner == "Bot")
                {
                    cout << "Bot wins this round! " << endl;
                    cout << "=============================" << endl;
                    current.deductBalance(cash);
                }
                else if (winner == "Draw")
                {
                    cout << "It's a draw! " << endl;
                    cout << "=============================" << endl;
                }
                current.newisTurn(false); // end player turn
            }
        }
        string fullGameRecord = "\nGame History " + to_string(recordCounter++) + " :\n" + gameRecord;
        gameHistory.push_back(fullGameRecord);
    }

    void playerBalance()
    {
        cout << endl
             << endl;
        cout << "===== Remaining Balance ===== " << endl;
        cout << endl;
        for (int i = 0; i < total; i++)
        {
            cout << "Player " << i + 1 << " : " << players[i].getBalance() << endl;
            cout << "-----------------------------" << endl;
        }
    }

    void saveGameRecord()
    {
        ofstream outFile("logs/record.txt", ios::app); // ios::app meaning that new data is appended to the existing content rather than overwriting it.
        if (outFile.is_open())
        {
            for (int i = 0; i < gameHistory.size(); i++)
            {
                outFile << gameHistory[i] << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Unable to open the file" << endl;
        }
    }
};

class StartRPS : public Game1
{
private:
    vector<PlayerGameResultData> playerGameData;

public:
    StartRPS()
    {
        playerGameData.clear();
    };

    void startRps()
    {
        Game1 game;
        bool play = true;
        char answer;

        game.setTotalPlayers();
        game.setPlayerWhoPlaysByID();
        game.setLow();
        game.setPlayers();
        game.getAllPlayersBalance();

        while (play)
        {
            game.playerTurn();
            game.playerBalance();
            game.saveGameRecord();

            cout << "Do you want to play again? (y/n): ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                // Re-initialize game if a player still has a balance
                bool allPlayersHaveBalance = true;
                vector<float> balances = game.getBalanceSummary();

                for (int i = 0; i < balances.size(); i++)
                {
                    if (game.getBalanceSummary()[i] <= 0)
                    {
                        allPlayersHaveBalance = false;
                        break;
                    }
                }
                if (allPlayersHaveBalance)
                {
                    play = true;
                }
                else
                {
                    cout << "One or more players have run out of balance. The game cannot continue." << endl;
                    play = false;
                }
            }
            else if (answer == 'n' || answer == 'N')
            {
                play = false;
                cout << "==========================================" << endl;
                cout << "Thank you for playing Rock Paper Scissors!" << endl;
                cout << "==========================================" << endl
                     << endl
                     << endl;
            }
            else
            {
                cout << "Invalid input" << endl;
                cin >> answer;
            }
        }

        // Create an empty fixed array of total players
        string playerGameStatus[game.getTotalPlayers()];
        PlayerGameResultData playerData;

        // Get player game data
        for (int i = 0; i < game.getTotalPlayers(); i++)
        {
            string result = game.getPlayers()[i].getGameResult();

            if (result == "Player")
            {
                playerGameStatus[i] = "WIN";
            }
            else if (result == "Bot")
            {
                playerGameStatus[i] = "LOSE";
            }
            else if (result == "Draw")
            {
                playerGameStatus[i] = "DRAW";
            }
            playerData.id = game.getPlayers()[i].getId();
            playerData.name = game.getPlayers()[i].getName();
            playerData.gameStatus = playerGameStatus[i];
            playerData.initialBalance = game.getPlayerStartingBalance()[i];
            playerData.finalBalance = game.getPlayers()[i].getBalance();
            playerGameData.push_back(playerData);
        }
    }
    // return player game data
    vector<PlayerGameResultData> getPlayerGameData()
    {
        return playerGameData;
    };
};
