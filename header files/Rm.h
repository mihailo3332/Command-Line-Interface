//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//

#ifndef RM_H
#define RM_H
#include "Command.h"
#include <iostream>
#include <filesystem>
namespace fs = filesystem;
using namespace std;

class Rm : public Command {
  public:

    Rm();

    ~Rm() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

};

#endif //RM_H
