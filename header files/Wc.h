//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//

#ifndef WC_H
#define WC_H
#include "Command.h"
#include <iostream>
#include <string>
#include <sstream>

class Wc: public Command {
  public:

    Wc();

    ~Wc() override;

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

};

#endif //WC_H
