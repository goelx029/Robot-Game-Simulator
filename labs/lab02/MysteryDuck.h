#ifndef LAB02_MSYTERYDUCK_H_
#define LAB02_MYSTERYDUCK_H_

#include <string>
#include "Duck.h"

class MysteryDuck : public Duck {

private:
  std::string description;
  std::string quack;

public:
  MysteryDuck(std::string descriptionText, std::string quackSound);
  std::string getDescription();
  void performQuack();
};

#endif
