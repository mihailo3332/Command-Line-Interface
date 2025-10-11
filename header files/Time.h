//
// Created by Mihailo Mitrovic on 31. 7. 2025..
//

#ifndef TIME_H
#define TIME_H

#include "Command.h"
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

class Time : public Command {
  public:

  Time();

  ~Time() override;

  bool hasOption() const override;

  bool hasArgument() const override;

  bool isFileType() const override;

  void execute(bool pipes) override;
};

#endif //TIME_H
