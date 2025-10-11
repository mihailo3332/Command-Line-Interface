#include <iostream>
using namespace std;

#include "header files/CLI.h"
#include "header files/Command.h"
#include "header files/Echo.h"

int main() {
    CLI* c1 = new CLI();
    c1->displayPrompt();
    while (c1->nextCommand()) {
        c1->displayPrompt();
    }

    return 0;
}