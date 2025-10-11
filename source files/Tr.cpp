//
// Created by Mihailo Mitrovic on 13. 8. 2025..
//
#include "../header files/Tr.h"

Tr::Tr() {
    this->comm_name = "tr";
    this->numberOfParams = 4;
}

Tr::~Tr() = default;

string Tr::getWhat() const {
    return this->what;
}

string Tr::getWith() const {
    return this->with;
}

void Tr::setWhat(string &st) {
    this->what = st;
}

void Tr::setWith(string &st) {
    this->with = st;
}

bool Tr::hasOption() const {
    return false;
}

bool Tr::hasArgument() const {
    return true;
}

bool Tr::isFileType() const {
    return false;
}

void Tr::execute(bool pipes) {
    string what = this->getWhat();
    what = what.substr(1, what.size() - 2);

    string with = this->getWith();
    if (!with.empty()) with = with.substr(1, with.size() - 2);

    string arg = this->getInputStream()->read();
    size_t pos = arg.find(what);

    if (!with.empty()) {
        while (pos != string::npos) {
            arg.replace(pos, what.length(), with);
            pos = arg.find(what);
        }
    } else {
        while (pos != string::npos) {
            arg.erase(pos, what.length());
            pos = arg.find(what);
        }
    }
    this->setInputStream(new StdInputStream(arg));
    if (!pipes)this->getOutputStream()->write(arg);
}
