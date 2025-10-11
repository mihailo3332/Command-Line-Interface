//
// Created by Mihailo Mitrovic on 15. 8. 2025..
//

#ifndef BATCH_H
#define BATCH_H
#include "Command.h"
#include "CLI.h"
#include "Parser.h"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

class Batch : public Command {
  public:

    Batch();

    ~Batch() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

    void setCLI(CLI* cli);

    private:

    CLI* m_cli = nullptr;

};

#endif //BATCH_H
