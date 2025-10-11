//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//

#ifndef TOUCH_H
#define TOUCH_H
#include "Command.h"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = filesystem;
using namespace std;

class Touch: public Command {
  public:

    Touch();

    ~Touch() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

};

#endif //TOUCH_H
