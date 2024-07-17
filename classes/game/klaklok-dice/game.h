#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "player.h"
#include "../../print/styling.h"
#include "../../player/player.h"

using namespace std;

class KlaKlokGame
{
private:
    int totalPlayers;
    double startingBalance;
    vector<int> playerIDs;
    vector<string> playerNames;
    vector<double> playerStartingBalance;
    vector<KlaKlokPlayer> players;

public:
    KlaKlokPrint styleMessage;

    // Constructor
    KlaKlokGame()
    {
        clearGameData();
    };

    // Total Players
    void setTotalPlayers()
    {
        // Get number of players
        int numPlayers;
        bool validInput = false;
        while (!validInput)
        {
            cout << "Enter number of players: ";
            cin >> numPlayers;

            // Check if input is valid
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
            }
            else if (numPlayers < 2 || numPlayers > 4)
            {
                cout << "Number of players should be 2-4!" << endl;
            }
            else
            {
                validInput = true;
            }
        }
        this->totalPlayers = numPlayers;
        cout << "======> Total players: " << totalPlayers << endl;
    };

    int getTotalPlayers()
    {
        return totalPlayers;
    };

    // Enter the player who want to play
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
                        cout << "Player " << playerData.name << " is ready to play!" << endl;
                        setStartingBalanceForSelectedPlayer(playerData);
                        playerIDs.push_back(playerData.id);
                        playerNames.push_back(playerData.name);
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

    // Get starting balance for each player
    vector<double> getPlayerStartingBalance()
    {
        return playerStartingBalance;
    };

    // Set starting balance for each player
    void setStartingBalanceForSelectedPlayer(const PlayerData &playerDat)
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
            else if (startingBal < 100 || startingBal > playerDat.balance)
            {
                cout << "Starting balance should be between 100 and " << playerDat.balance << "!" << endl;
            }
            else
            {
                validInput = true;
            }
        }
        this->playerStartingBalance.push_back(startingBal);
    };

    // Lowest Starting Balance
    void setLowestStartingBalance()
    {
        double lowestBal = playerStartingBalance[0];
        for (int i = 1; i < playerStartingBalance.size(); i++)
        {
            if (playerStartingBalance[i] < lowestBal)
            {
                lowestBal = playerStartingBalance[i];
            }
        }
        this->startingBalance = lowestBal;
    };

    double getStartingBalance()
    {
        return startingBalance;
    };

    // Set Players
    void setPlayers()
    {
        // Create players array
        for (int i = 0; i < totalPlayers; i++)
        {
            KlaKlokPlayer player;
            this->players.push_back(player);

            // Set player ID
            players[i].setId(playerIDs[i]);

            // Set player name
            players[i].setName(playerNames[i]);

            // Set starting balance for each player
            players[i].setBalance(playerStartingBalance[i]);
        }
    };

    // Get Players
    vector<KlaKlokPlayer> getPlayers()
    {
        return this->players;
    };

    // Print players balance
    void getAllPlayersBalance()
    {
        styleMessage.printHeading("All Players Balance");
        for (int i = 0; i < totalPlayers; i++)
        {
            cout << "#" << i + 1 << " " << playerNames[i] << "'s balance: $" << this->players[i].getBalance() << endl;
        }
        styleMessage.printFrame("All Players Balance");
    };

    // Check if a player exceeds 10 times the starting balance
    bool isPlayerExceedsLimit()
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            if (players[i].getBalance() > (startingBalance * 10))
            {
                return true;
            }
        }
        return false;
    };

    // Check if only one player is left has balance
    bool isOnePlayerLeft()
    {
        int count = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (players[i].getBalance() > 0)
            {
                count++;
            }
        }
        return count == 1;
    };

    // Check if no player has balance
    bool isNoPlayerLeft()
    {
        int count = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (players[i].getBalance() <= 0)
            {
                count++;
            }
        }
        return count == totalPlayers;
    };

    // Player turns
    void playerTurns()
    {
        for (int i = 0; i < this->totalPlayers; i++)
        {
            KlaKlokPlayer &currentPlayer = this->players[i];

            // Check if player has balance
            if (currentPlayer.getBalance() <= 0)
            {
                cout << "#" << i + 1 << " " << currentPlayer.getName() << " has no balance left!" << endl;
                continue;
            }

            // Check if player is betting
            cout << endl
                 << "=====> Player #" << i + 1 << " " << currentPlayer.getName() << "'s turn <=====" << endl;
            currentPlayer.setIsTurn(true);
            while (currentPlayer.getIsTurn() == true)
            {
                // Get input from 1-6
                int input;
                bool validInput = false;
                while (!validInput)
                {
                    cout << "Enter a number from 1 to 6: ";
                    cin >> input;
                    // Check if input is valid
                    if (cin.fail() || input < 1 || input > 6)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number from 1 to 6." << endl;
                    }

                    // Check if player already guessed the number
                    else if (currentPlayer.inputExists(input))
                    {
                        cout << "You already guessed this number! Please enter a different number." << endl;
                    }
                    else
                    {
                        validInput = true;
                    }
                }
                currentPlayer.addInputValues(input);

                // Get bet amount
                double betAmount;
                validInput = false;
                while (!validInput)
                {
                    cout << "Enter bet amount: ";
                    cin >> betAmount;
                    // Check if input is valid
                    if (cin.fail() || betAmount <= 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a valid bet amount." << endl;
                    }
                    else if (betAmount > currentPlayer.getBalance())
                    {
                        cout << "Bet amount should be less than or equal to your balance! Your balance: $" << currentPlayer.getBalance() << endl;
                    }
                    else if (betAmount > currentPlayer.getCanBetAmount())
                    {
                        cout << "Can not bet! You only have $" << currentPlayer.getCanBetAmount() << " left!" << endl;
                    }
                    else
                    {
                        validInput = true;
                    }
                }
                currentPlayer.addBetAmounts(betAmount);

                if (currentPlayer.getCanBetAmount() > 0 && currentPlayer.getInputValues().size() < 6)
                {
                    // Continue betting
                    char continueBetting;
                    validInput = false;
                    while (!validInput)
                    {
                        cout << "Continue betting? (y/n): ";
                        cin >> continueBetting;
                        // Check if input is valid
                        if (cin.fail() || (continueBetting != 'y' && continueBetting != 'n'))
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input! Please enter y or n." << endl;
                        }
                        else
                        {
                            validInput = true;
                        }
                    }

                    // Set isBetting
                    bool isTurn = (continueBetting == 'y') ? true : false;
                    currentPlayer.setIsTurn(isTurn);
                }
                else
                {
                    cout << endl;
                    currentPlayer.setIsTurn(false);
                }
            }
        }
    }

    // Randomize 3 dice values from 1-6
    vector<int> randomizeDiceValues()
    {
        vector<int> diceValues;

        // Seed the random number generator with the current time
        srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 0; i < 3; i++)
        {
            int randomVal = (rand() % 6) + 1;
            diceValues.push_back(randomVal);
        }
        return diceValues;
    };

    // Check if player guessed the number and get the bet amount, then add balance if correct, deduct balance if wrong
    void checkPlayerGuess(const vector<int> &diceValues)
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            KlaKlokPlayer &currentPlayer = players[i];
            vector<int> correctGuesses;

            // Check for wrong guesses and deduct balance
            for (int j = 0; j < currentPlayer.getInputValues().size(); j++)
            {
                if (find(diceValues.begin(), diceValues.end(), currentPlayer.getInputValues()[j]) == diceValues.end())
                {
                    // cout << "Player " << i + 1 << " guessed the number " << diceValues[j] << " wrongly!" << endl;
                    currentPlayer.deductBalance(currentPlayer.getBetAmounts()[j]);
                }
                else
                {
                    // Add the correct guess to the player's correct guesses
                    correctGuesses.push_back(currentPlayer.getInputValues()[j]);
                }
            }

            // Check for correct guesses and add balance accordingly with the dice result
            for (int j = 0; j < correctGuesses.size(); j++)
            {
                // Count the number of correct guesses
                int count = std::count(diceValues.begin(), diceValues.end(), correctGuesses[j]);
                string abbre = "";

                switch (count)
                {
                case 1:
                    abbre = "once";
                    break;
                case 2:
                    abbre = "twice";
                    break;
                case 3:
                    abbre = "thrice";
                    break;
                default:
                    abbre = "";
                    break;
                }

                double amount = currentPlayer.getBetAmounts()[j] * count;
                currentPlayer.addBalance(amount);
                cout << "Player " << i + 1 << " guessed the number " << correctGuesses[j] << " correctly " << abbre << " and earned " << amount << endl;
            }
        }
    }

    // Reset player input values and bet amounts
    void resetPlayerValues()
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            players[i].clearInputValues();
            players[i].clearBetAmounts();
        }
    };

    // Clear all data
    void clearGameData()
    {
        totalPlayers = 0;
        startingBalance = 0;
        players.clear();
        playerStartingBalance.clear();
    };
};

class StartKlaKlokGame : public KlaKlokGame
{
private:
    vector<PlayerGameResultData> playerGameData;

public:
    StartKlaKlokGame()
    {
        playerGameData.clear();
    };

    void startGame()
    {
        // Object instance
        KlaKlokPrint message;
        KlaKlokGame game;

        // Display heading message
        message.headingMsg();

        // Input number of players and starting balance
        game.setTotalPlayers();

        // Enter the player who want to play
        game.setPlayerWhoPlaysByID();

        // Set lowest starting balance
        game.setLowestStartingBalance();

        // Create players array
        game.setPlayers();

        // Get players balance
        game.getAllPlayersBalance();

        // Start the game
        cout << "Game started!" << endl;

        // Game loop, if a player exceeds 10 times the starting balance or only one player is left, end the game
        while (!game.isPlayerExceedsLimit() && !game.isOnePlayerLeft() && !game.isNoPlayerLeft())
        {
            // Player turns
            game.playerTurns();

            // Randomize dice values
            vector<int> diceValues = game.randomizeDiceValues();

            // Display dice values
            styleMessage.randomDiceMsg(diceValues);

            // Check if player guessed the number and get the bet amount, then add balance if correct, deduct balance if wrong
            game.checkPlayerGuess(diceValues);

            // Get players balance
            game.getAllPlayersBalance();

            // Reset player input values and bet amounts
            game.resetPlayerValues();
        }
        cout << endl;

        // Create an empty fixed array of total players
        string playerGameStatus[game.getTotalPlayers()];

        // Check win condition
        if (game.isPlayerExceedsLimit())
        {
            // Display winner
            cout << "================WINNER================" << endl;
            for (int i = 0; i < game.getTotalPlayers(); i++)
            {
                double playerBal = game.getPlayers()[i].getBalance();
                string playerName = game.getPlayers()[i].getName();
                if (playerBal > (game.getStartingBalance() * 10))
                {
                    cout << "# " << i + 1 << " " << playerName << " is the winner with $" << playerBal << endl;
                    playerGameStatus[i] = "WIN";
                }
                else
                {
                    playerGameStatus[i] = "LOSE";
                }
            }
            cout << "======================================" << endl
                 << endl;
        }
        else if (game.isOnePlayerLeft())
        {
            // Display winner
            cout << "================WINNER================" << endl;
            for (int i = 0; i < game.getTotalPlayers(); i++)
            {
                double playerBal = game.getPlayers()[i].getBalance();
                string playerName = game.getPlayers()[i].getName();
                if (playerBal > 0)
                {
                    cout << "# " << i + 1 << " " << playerName << " is the winner with $" << playerBal << endl;
                    playerGameStatus[i] = "WIN";
                }
                else
                {
                    playerGameStatus[i] = "LOSE";
                }
            }
            cout << "======================================" << endl
                 << endl;
        }
        else if (game.isNoPlayerLeft())
        {
            cout << "================ DRAW ================" << endl;
            cout << "All players ran out of money!" << endl;
            cout << "======================================" << endl
                 << endl;
            for (int i = 0; i < game.getTotalPlayers(); i++)
            {
                playerGameStatus[i] = "DRAW";
            }
        }
        else
        {
            cout << "Game ended!" << endl;
        }

        // Get player game data
        for (int i = 0; i < game.getTotalPlayers(); i++)
        {
            PlayerGameResultData playerData;
            playerData.id = game.getPlayers()[i].getId();
            playerData.name = game.getPlayers()[i].getName();
            playerData.gameStatus = playerGameStatus[i];
            playerData.initialBalance = game.getPlayerStartingBalance()[i];
            playerData.finalBalance = game.getPlayers()[i].getBalance();
            playerGameData.push_back(playerData);
        }

        // Display exit message
        message.exitMsg();
    }

    // return player game data
    vector<PlayerGameResultData> getPlayerGameData()
    {
        return playerGameData;
    };
};
