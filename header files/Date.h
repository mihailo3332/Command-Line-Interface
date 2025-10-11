//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//

#ifndef DATE_H
#define DATE_H
#include "Command.h"
#include <ctime>
#include <iostream>
using namespace std;

class Date: public Command {
  public:

    Date();

    ~Date() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

};


#endif //DATE_H
