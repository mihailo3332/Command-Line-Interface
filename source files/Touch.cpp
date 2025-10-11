//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//
#include "../header files/Touch.h"

Touch::Touch() {
    this->comm_name = "touch";
    this->numberOfParams = 2;
}

Touch::~Touch() = default;

bool Touch::hasOption() const {
    return false;
}

bool Touch::hasArgument() const {
    return true;
}

bool Touch::isFileType() const {
    return true;
}

void Touch::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    if (arg[arg.size() - 1] == ' ') arg = arg.substr(0, arg.size() - 1);
    if (fs::exists(arg)) {
        cout << "File " << arg << " already exists.";
    } else {
        ofstream file(arg);
        if (file.is_open()) {
            cout << "File " << arg << " opened successfully.";
        }else {
            cout << "File " << arg << " did not open successfully.";
        }
    }
}
