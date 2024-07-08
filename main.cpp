#include <iostream>
#include "classes/print/welcome.cpp"
#include "classes/player/player.cpp"
using namespace std;

int main()
{
    Welcome welcome;
    welcome.printWelcome();

    Player player;
    player.listPlayers();

    player.registerPlayer();

    return 0;
}