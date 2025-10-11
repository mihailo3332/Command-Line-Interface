//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#include "../header files/Echo.h"

#include "../header files/CLI.h"

Echo::Echo() {
    this->comm_name = "echo";
    this->numberOfParams = 2;
}

Echo::~Echo() = default;

bool Echo::hasOption() const {
    return false;
}

bool Echo::hasArgument() const {
    return true;
}

bool Echo::isFileType() const {
    return false;
}

void Echo::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    if (!arg.empty() && !pipes) this->getOutputStream()->write(arg);
}
