//
// Created by Mihailo Mitrovic on 15. 8. 2025..
//

#ifndef HEAD_H
#define HEAD_H
#include "Command.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Head : public Command {
  public:

    Head();

    ~Head() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;
};

#endif //HEAD_H
