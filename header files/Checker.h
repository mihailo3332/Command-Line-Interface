//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#ifndef CHECKER_H
#define CHECKER_H
#include "Command.h"
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

class Checker {
public:

    Checker();

    ~Checker();

    static void printError();

    bool checkErrors(Command *c, vector<string> comm_line, bool pipes, string poz);

private:
    static bool checkParams(Command* c, vector<string> comm_line, bool pipes, string pos);

    static vector<int> checkSyntax(Command *c, vector<string> comm_line, bool pipes, string pos);

    static bool inputOutputRedirection(Command* c, vector<string>& comm_line, int& numOfParams);

    static bool outpuRedirection(Command* c, vector<string>& comm_line, int& numOfParams);

    static bool inputRedirection(Command* c, vector<string>& comm_line, int& numOfParams);

    static bool middlePipes(vector<string>& comm_line, int& numOfParams, bool& pipes, string& pos);

    static bool frontPipes(vector<string>& comm_line, int& numOfParams, bool& pipes, string& pos);

    static bool rearPipes(Command* c, vector<string>& comm_line, int& numOfParams, bool& pipes, string& pos);

    static bool checkInput(const string &param, Command *c, bool setOption, bool redirection);

};

#endif //CHECKER_H
