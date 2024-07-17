#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "../player/player.h"
#include "../game/klaklok-dice/game.h"

using namespace std;

class Menu
{
public:
    void printMainMenu()
    {

        cout << endl
             << "-------[ Mini Game Hub Menu ]-------" << endl;
        cout << ">> 1. List all players" << endl;
        cout << ">> 2. Register a new player" << endl;
        cout << ">> 3. Transfer balance" << endl;
        cout << ">> 4. Find player by ID" << endl;
        cout << ">> 5. Find player by Name" << endl;
        cout << ">> 6. PLAY GAMES" << endl;
        cout << ">> 7. Exit" << endl;
        cout << "------------------------------------" << endl;
    }

    void printGameMenu()
    {
        cout << endl
             << "-------[ AVAILABLE GAMES ]-------" << endl;
        cout << ">> 1. KlaKlok Dice V1 (2-4 Players)" << endl;
        cout << ">> 2. Tic Tac Toe (2 Players)" << endl;
        cout << ">> 3. Back" << endl;
        cout << "---------------------------------" << endl;
    }
};

class MenuSelection : public Menu
{

private:
    Player player;

public:
    MenuSelection()
    {
        Player players;
        this->player = players;
    }

    void mainMenuSelection()
    {
        int choice;
        bool isMenuRunning = true;
        while (isMenuRunning)
        {
            printMainMenu();
            cout << "~~~ Enter a choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 7)
            {
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Switch case and break out of While loop
                switch (choice)
                {
                case 1:
                    player.listPlayers();
                    break;
                case 2:
                    player.registerPlayer();
                    break;
                case 3:
                    player.transferBalance();
                    break;
                case 4:
                    player.findPlayerByID();
                    break;
                case 5:
                    player.findPlayerByName();
                    break;
                case 6:
                    gameMenuSelection();
                    isMenuRunning = false;
                    break;
                case 7:
                    cout << "Exiting..." << endl;
                    isMenuRunning = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    isMenuRunning = false;
                    break;
                }
            }
        }
    }

    void gameMenuSelection()
    {
        int choice;
        bool isMenuRunning = true;
        while (isMenuRunning)
        {
            printGameMenu();
            cout << "~~~ Enter a choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3)
            {
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                isMenuRunning = false;

                // Game Objects
                StartKlaKlokGame klaklokGame;
                bool isKlaKlokGameRunning = false;

                // Switch case and break out of While loop
                switch (choice)
                {
                case 1:
                    isKlaKlokGameRunning = true;
                    while (isKlaKlokGameRunning)
                    {
                        klaklokGame.startGame();

                        vector<PlayerGameResultData> resultDat = klaklokGame.getPlayerGameData();

                        // Update player data in file
                        for (int i = 0; i < resultDat.size(); i++)
                        {
                            player.updatePlayerBalance(resultDat[i].id, resultDat[i].initialBalance, resultDat[i].finalBalance);
                            player.updatePlayerGameStats(resultDat[i].id, resultDat[i].gameStatus);
                        }

                        // Write game results to file
                        player.updateDataFile();

                        // Exit game and return to main menu
                        isKlaKlokGameRunning = false;
                        isMenuRunning = true;
                    }
                    break;
                case 2:
                    cout << "Tic Tac Toe (2 Players)" << endl;
                    break;
                case 3:
                    cout << "Back" << endl;
                    mainMenuSelection();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    isMenuRunning = true;
                    break;
                }
            }
        }
    }
};
