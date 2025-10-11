//
// Created by Mihailo Mitrovic on 13. 7. 2025..
//

#include "../header files/Parser.h"

Parser::Parser(Reader *reader) {
    this->m_reader = reader;
}

Parser::~Parser() {
    delete m_reader;
}

vector<string> Parser::parseLine() {
    string comm;
    if (this->m_reader->endOfRead()) {
        return {};
    }
    comm = this->m_reader->readLine();
    return parse(comm);
}


vector<string> Parser::parse(string &line) {
    vector<string> command;
    string tmp;
    int i = 0;
    while (i < line.size()) {
        if (line[i] == '"') {
            tmp += line[i++];
            while (i < line.size() && line[i] != '"') {
                tmp += line[i++];
            }
            tmp += line[i++];
            if (!tmp.empty()) {
                command.push_back(tmp);
                tmp = "";
            }
        } else {
            while (line[i] != ' ' && line[i] != '\t' && i < line.size()) {
                tmp += line[i++];
            }
            i++;
            if (!tmp.empty()) {
                command.push_back(tmp);
                tmp = "";
            }
        }
    }
    if (line[line.length() - 1] == ' ' && line[line.length() - 2] != '"') command[command.size() - 1] += ' ';
    return command;
}
