//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#ifndef ECHO_H
#define ECHO_H

#include "Command.h"
#include <iostream>
using namespace std;

class Echo: public Command {
  public:

    Echo();

    ~Echo() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

};


#endif //ECHO_H
