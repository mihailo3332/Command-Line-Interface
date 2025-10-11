//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//
#include "../header files/Truncate.h"

Truncate::Truncate() {
    this->comm_name = "truncate";
    this->numberOfParams = 2;
}

Truncate::~Truncate() = default;

bool Truncate::hasOption() const {
    return false;
}

bool Truncate::hasArgument() const {
    return true;
}

bool Truncate::isFileType() const {
    return true;
}

void Truncate::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    if (arg[arg.size() - 1] == ' ') arg = arg.substr(0, arg.size() - 1);
    if (fs::exists(arg)) {
        ofstream file(arg, std::ios::trunc);
        cout << "Content of a file " << arg << " deleted successfully.";
    } else {
        cout << "Error, file " << arg << " does not exist.";
    }
}
