//
// Created by Mihailo Mitrovic on 15. 8. 2025..
//
#include "../header files/Batch.h"

Batch::Batch() {
    this->comm_name = "batch";
    this->numberOfParams = 2;
}

Batch::~Batch() = default;

bool Batch::hasOption() const {
    return false;
}

bool Batch::hasArgument() const {
    return true;
}

bool Batch::isFileType() const {
    return false;
}

void Batch::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    stringstream ss(arg);
    string line;
    while (getline(ss, line, '\n')) {
        vector<string> command = Parser::parse(line);
        if (command.empty()) return;
        if (CLI::containsPipes(command)) {
            this->m_cli->handlePipes(command);
        } else {
            Command *c = this->m_cli->findCommand(command, "", pipes, "middle");
        }
        cout << endl;
    }
}

void Batch::setCLI(CLI *cli) {
    this->m_cli = cli;
}
