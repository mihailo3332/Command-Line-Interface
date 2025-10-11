//
// Created by Mihailo Mitrovic on 15. 8. 2025..
//
#include "../header files/Checker.h"
#include "../header files/CLI.h"
#include "../header files/Tr.h"

Checker::Checker() = default;

Checker::~Checker() = default;

void Checker::printError() {
    cout << "Error, you inputted more arguments than required.";
}

bool Checker::middlePipes(vector<string>& comm_line, int &numOfParams, bool &pipes, string &pos) {
    if (comm_line.size() > numOfParams - 1) {
        printError();
        return false;
    }
    return true;
}

bool Checker::frontPipes(vector<string> &comm_line, int &numOfParams, bool &pipes, string &pos) {
    int maxParams = numOfParams + 1;
    if (comm_line.size() == maxParams && CLI::containsInputRedirection(comm_line)) {
        if (comm_line[1] != "<") {
            printError();
            return false;
        }
        return true;
    }if (comm_line.size() > numOfParams) {
        printError();
        return false;
    }
    return true;
}

bool Checker::rearPipes(Command *c, vector<string> &comm_line, int &numOfParams, bool &pipes, string &pos) {
    if (comm_line.size() >= numOfParams && CLI::containsOutputRedirection(comm_line)) {
        int maxParams = numOfParams + 1;
        if (comm_line.size() == maxParams) {
            if (!((find(comm_line.begin(), comm_line.end(), ">") != comm_line.end() && comm_line.back() != ">") ||
                  (find(comm_line.begin(), comm_line.end(), ">>") != comm_line.end() && comm_line.back() !=
                   ">>"))) {
                printError();
                return false;
            }
        } else if (comm_line.size() == numOfParams) {
            if (Tr *tr = dynamic_cast<Tr *>(c)) {
                if (tr->getWith().empty()) {
                    if (comm_line[comm_line.size() - 2] != ">" && comm_line[comm_line.size() - 2] != ">>") {
                        printError();
                        return false;
                    }
                } else {
                    if (comm_line.back().front() != '>') {
                        printError();
                        return false;
                    }
                }
            } else if (comm_line.back().front() != '>') {
                printError();
                return false;
            }
        } else if (comm_line.size() > numOfParams) {
            printError();
            return false;
        }
    } else if (comm_line.size() >= numOfParams) {
        printError();
        return false;
    }
    return true;
}

bool Checker::inputOutputRedirection(Command *c, vector<string> &comm_line, int &numOfParams) {
    int maxParams = numOfParams + 3;
    if (comm_line.size() == maxParams) {
        if ((find(comm_line.begin(), comm_line.end(), "<") == comm_line.end() &&
            comm_line.back()!= "<") &&
            (((find(comm_line.begin(), comm_line.end(), ">") == comm_line.end() &&
                comm_line.back()!= ">")||
              ((find(comm_line.begin(), comm_line.end(), ">>") == comm_line.end() &&
                  comm_line.back() != ">>"))))) {
            printError();
            return false;
        }
    } else if (comm_line.size() > numOfParams && comm_line.size() < maxParams) {
        if (Tr *tr = dynamic_cast<Tr *>(c)) {
            if (comm_line[1].front() != '<' && comm_line.back().front() != '>' &&
                comm_line.back().size() > 2) {
                printError();
                return false;
            }
        } else {
            int i = c->hasOption() ? 2 : 1;
            while (i < comm_line.size()) {
                if ( (comm_line[i].front() != '<' && comm_line[i].front() != '>' &&
                    (comm_line[i].front() != '>' && comm_line[i].front() + 1 != '>') &&
                    comm_line[i - 1].front() != '<' && comm_line[i - 1].front() != '>' &&
                    (comm_line[i - 1].front() != '>' && comm_line[i - 1].front() + 1 != '>')) || comm_line[i].front() == '"'){
                    printError();
                    return false;
                }
                i++;
            }
        }
    } else if (comm_line.size() > numOfParams) {
        printError();
        return false;
    }
    return true;
}

bool Checker::outpuRedirection(Command *c, vector<string> &comm_line, int &numOfParams) {
    int maxParams = numOfParams + 2;
    if (comm_line.size() == maxParams) {
        if (!((find(comm_line.begin(), comm_line.end(), ">") != comm_line.end() && comm_line.back() != ">") ||
              (find(comm_line.begin(), comm_line.end(), ">>") != comm_line.end() && comm_line.back() != ">>"))) {
            printError();
            return false;
        }
    } else if (comm_line.size() > numOfParams && comm_line.size() < maxParams) {
        if (Tr *tr = dynamic_cast<Tr *>(c)) {
            if (tr->getWith().empty()) {
                if (comm_line[comm_line.size() - 2].front() != '>') {
                    printError();
                    return false;
                }
            }else if (comm_line.back().front() != '>') {
                printError();
                return false;
            }
        }else if (comm_line.back().front() != '>') {
            printError();
            return false;
        }
    } else if (comm_line.size() > numOfParams) {
        printError();
        return false;
    }
    return true;
}

bool Checker::inputRedirection(Command *c, vector<string> &comm_line, int &numOfParams) {
    int maxParams = numOfParams + 1;
    if (comm_line.size() == maxParams) {
        if (find(comm_line.begin(), comm_line.end(), "<") == comm_line.end() &&
            comm_line.back() != "<") {
            printError();
            return false;
        }
    }
    if (comm_line.size() == numOfParams) {
        if (Tr *tr = dynamic_cast<Tr *>(c)) {
            if (comm_line[1].front() != '<') {
                printError();
                return false;
            }
        } else if (comm_line.back().front() != '<') {
            printError();
            return false;
        }
    }
    if (comm_line.size() > maxParams) {
        printError();
        return false;
    }
    return true;
}

bool Checker::checkParams(Command *c, vector<string> comm_line, bool pipes, string pos) {
    int numOfParams = c->getNumberOfParams();

    if (pipes && pos == "middle") {
        return middlePipes(comm_line, numOfParams, pipes, pos);
    }
    if (pipes && pos == "front") {
        return frontPipes(comm_line, numOfParams, pipes, pos);
    }
    if (!pipes && pos == "rear") {
        return rearPipes(c, comm_line, numOfParams, pipes, pos);
    }
    if (CLI::containsOutputRedirection(comm_line) && CLI::containsInputRedirection(comm_line)) {
        return inputOutputRedirection(c, comm_line, numOfParams);
    }
    if (CLI::containsOutputRedirection(comm_line)) {
        return outpuRedirection(c, comm_line, numOfParams);
    }
    if (CLI::containsInputRedirection(comm_line)) {
        return inputRedirection(c, comm_line, numOfParams);
    }
    if (comm_line.size() > numOfParams) {
        printError();
        return false;
    }
    return true;
}

bool Checker::checkInput(const string &param, Command *c, bool setOption, bool redirection) {
    regex argTypeRegex(R"(^("[^"]*"|[A-Za-z0-9_\/-]+\.txt\s?|\w+)$)");
    regex fileTypeRegex(R"(^[A-Za-z0-9_\/-]+\.txt\s?$)");
    regex headOption(R"(^-n[0-9]{1,5}$)");
    regex trRegex(R"(^"[^"]*"$)");

    if (c->getName() == "wc" && setOption) {
        if (param == "-w" || param == "-c") return true;
        return false;
    }
    if (Tr *tr = dynamic_cast<Tr *>(c)) {
        if (!tr->getWhat().empty() && param == tr->getWhat()) {
            return regex_match(param, trRegex);
        }
        if (!tr->getWith().empty() && param == tr->getWith()) {
            return regex_match(param, trRegex);
        }
    }
    if (c->getName() == "head" && setOption) {
        return regex_match(param, headOption);
    }

    if (c->isFileType() || redirection) {
        return regex_match(param, fileTypeRegex);
    }
    return regex_match(param, argTypeRegex);
}


vector<int> Checker::checkSyntax(Command *c, vector<string> comm_line, bool pipes, string poz) {
    vector<int> result;
    vector<int> positions(comm_line.size());
    int pos = 0;
    for (int i = 0; i < comm_line.size(); i++) {
        if (i > 0) pos++;
        positions[i] = pos;
        pos += comm_line[i].size();
    }
    for (int j = 1; j < comm_line.size(); j++) {
        string param = comm_line[j];
        bool iR = (!param.empty() && param.front() == '<');
        bool oR = (!param.empty() && param.front() == '>');
        string var = param;

        if (iR) {
            if (param.size() == 1) {
                if (j < comm_line.size() - 1) {
                    j++;
                    param = comm_line[j];
                    var = param;
                }
            } else {
                var = param.substr(1, param.size() - 1);
            }
        }
        if (oR) {
            if (param.size() == 1 || (param.size() == 2 && param[1] == '>')) {
                if (j < comm_line.size() - 1) {
                    j++;
                    param = comm_line[j];
                    var = param;
                }
            }
            if (param.size() > 1 && param[1] == '>') var = param.substr(2, param.size());
            else var = param.substr(1, param.size());
        }

        bool setOption = false;
        if ((c->getName() == "wc" || c->getName() == "head") && j == 1) setOption = true;
        bool redirection = iR || oR;

        if (!checkInput(var, c, setOption, redirection)) {
            for (int k = 0; k < param.size(); k++) {
                result.push_back(positions[j] + k);
            }
        }
    }
    return result;
}

bool Checker::checkErrors(Command *c, vector<string> comm_line, bool pipes, string poz) {
    vector<int> rez = checkSyntax(c, comm_line, pipes, poz);
    if (!rez.empty()) {
        cout << "Error - unexpected characters: " << endl;
        string line;
        for (const string &s: comm_line) {
            line += s + " ";
        }
        cout << line << endl;
        for (int i = 0; i < line.size(); i++) {
            if (find(rez.begin(), rez.end(), i) != rez.end()) cout << '^';
            else cout << ' ';
        }
        return false;
    }
    return checkParams(c, comm_line, pipes, poz);
}
