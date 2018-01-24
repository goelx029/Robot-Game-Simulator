
#include "DecoyDuck.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

DecoyDuck::DecoyDuck() { }

string DecoyDuck::getDescription() {
    string descriptionText = "a plastic decoy ducky";
    return descriptionText;
}

void DecoyDuck::performQuack() {
    cout << "..." << endl;
}
