//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#include "../header files/Command.h"

Command::Command() = default;

Command::~Command() = default;

void Command::execute(bool pipes) {
}

bool Command::hasOption() const {
    return false;
}

bool Command::hasArgument() const {
    return false;
}

bool Command::isFileType() const {
    return false;
}

string Command::getName() const {
    return comm_name;
}

string Command::getOption() const {
    return comm_option;
}

int Command::getNumberOfParams() const {
    return this->numberOfParams;
}

string Command::getArgument() const {
    return comm_argument;
}

InputStream *Command::getInputStream() const {
    return this->in_stream;
}

OutputStream *Command::getOutputStream() const {
    return this->out_stream;
}

void Command::setOption(const string &option) {
    this->comm_option = option;
}

void Command::setArgument(const string &argument) {
    this->comm_argument = argument;
}

void Command::setInputStream(InputStream *inputStream) {
    this->in_stream = inputStream;
}

void Command::setOutputStream(OutputStream *outputStream) {
    this->out_stream = outputStream;
}

void Command::slice() {
    if (!this->hasArgument()) return;

    string arg = this->getInputStream()->read();

    string name = this->getName();

    size_t optLength = this->hasOption() ? this->getOption().length() : 0;

    size_t limit = 512 - name.length() - optLength;

    if (arg.length() > limit) {
        arg = arg.substr(0, limit);
        if (StdInputStream *std = dynamic_cast<StdInputStream *>(this->getInputStream())) {
            this->setInputStream(new StdInputStream(arg));
        } else if (FileInputStream *file = dynamic_cast<FileInputStream *>(this->getInputStream())) {
            this->setInputStream(new FileInputStream(arg));
        }
    }
}
