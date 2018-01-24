
#include "MysteryDuck.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

MysteryDuck::MysteryDuck(std::string descriptionText, std::string quackSound)
{
  description = descriptionText;
  quack = quackSound;
}

string MysteryDuck::getDescription() {
    return description;
}

void MysteryDuck::performQuack() {
    cout << quack << endl;
}
