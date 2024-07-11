#include <iostream>
#include "classes/print/welcome.h"
#include "classes/main/menu.h"
using namespace std;

int main()
{
    Welcome welcome;
    welcome.printWelcome();

    MenuSelection menu;
    menu.mainMenuSelection();

    return 0;
}