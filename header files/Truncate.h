//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//

#ifndef TRUNCATE_H
#define TRUNCATE_H
#include "Command.h"
#include <fstream>
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

class Truncate : public Command {
  public:

    Truncate();

    ~Truncate() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;
};

#endif //TRUNCATE_H
