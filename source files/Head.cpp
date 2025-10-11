//
// Created by Mihailo Mitrovic on 15. 8. 2025..
//
#include "../header files/Head.h"

Head::Head() {
    this->comm_name = "head";
    this->numberOfParams = 3;
}

Head::~Head() = default;

bool Head::hasOption() const {
    return true;
}

bool Head::hasArgument() const {
    return true;
}

bool Head::isFileType() const {
    return false;
}

void Head::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    string opt = this->getOption();
    int num = stoi(opt.substr(2, opt.size()));
    string pass;
    stringstream ss(arg);
    string word;
    for (int i = 0; i < num; i++) {
        getline(ss, pass);
        word += pass;
        if (i != num - 1) word += "\n";
    }
    if (!pipes)this->getOutputStream()->write(word);
    this->setInputStream(new StdInputStream(word));
}
