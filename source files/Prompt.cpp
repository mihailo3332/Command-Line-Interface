//
// Created by Mihailo Mitrovic on 17. 7. 2025..
//
#include "../header files/Prompt.h"

Prompt::Prompt() {
    this->comm_name = "prompt";
    this->numberOfParams = 2;
}

Prompt::~Prompt() = default;

void Prompt::setCLI(CLI *cli) {
    this->m_cli = cli;
}

string Prompt::getPrompt() const {
    return this->prompt;
}

void Prompt::setPrompt(string &pr) {
    this->prompt = pr;
}

bool Prompt::hasOption() const {
    return false;
}

bool Prompt::hasArgument() const {
    return true;
}

bool Prompt::isFileType() const {
    return false;
}

void Prompt::execute(bool pipes) {
    string arg = this->getInputStream()->read();
    this->m_cli->m_prompt->setPrompt(arg);
}
