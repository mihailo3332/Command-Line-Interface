//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//
#include "../header files/Rm.h"

Rm::Rm() {
    this->comm_name = "rm";
    this->numberOfParams = 2;
}

Rm::~Rm() = default;

bool Rm::hasOption() const {
    return false;
}

bool Rm::hasArgument() const {
    return true;
}

bool Rm::isFileType() const {
    return true;
}

void Rm::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    if (arg[arg.size() - 1] == ' ') arg = arg.substr(0, arg.size() - 1);
    if (fs::exists(arg)) {
        fs::remove(arg);
        cout << "File " << arg << " removed successfully.";
    } else {
        cout << "Error, file "<< arg << " does not exist.";
    }
}
