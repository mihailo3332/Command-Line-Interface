//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//
#include "../header files/Wc.h"

Wc::Wc() {
    this->comm_name = "wc";
    this->numberOfParams = 3;
}

Wc::~Wc() = default;

bool Wc::hasOption() const {
    return true;
}

bool Wc::hasArgument() const {
    return true;
}

bool Wc::isFileType() const {
    return false;
}

void Wc::execute(bool pipes) {
    string opt = this->getOption();
    string arg = this->getInputStream()->read();
    int cnt = 0;
    string tmp;
    if (opt == "-w") {
        stringstream ss(arg);
        while (ss >> arg) cnt++;
        if (!pipes)this->getOutputStream()->write(to_string(cnt));
    } else if (opt == "-c") {
        for (const char &c: arg) {
            if (c != '\n') cnt++;
        }
        if (!pipes)this->getOutputStream()->write(to_string(cnt));
    }
}
