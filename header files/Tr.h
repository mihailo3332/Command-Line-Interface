//
// Created by Mihailo Mitrovic on 13. 8. 2025..
//

#ifndef TR_H
#define TR_H
#include "Command.h"
#include <iostream>
#include <string>
using namespace std;

class Tr: public Command {
  public:

    Tr();

    ~Tr() override;

    string getWhat() const;

    string getWith() const;

    void setWhat(string&);

    void setWith(string&);

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

private:
    string what;
    string with;

};

#endif //TR_H
