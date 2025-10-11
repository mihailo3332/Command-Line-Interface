//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#include "../header files/CLI.h"
#include "../header files/Prompt.h"
#include "../header files/Tr.h"
#include "../header files/Batch.h"

map<string, unique_ptr<Command>> &getCommandMap() {
    static map<string, unique_ptr<Command>> comms;

    if (comms.empty()) {
        comms.emplace("echo", make_unique<Echo>());
        comms.emplace("prompt", make_unique<Prompt>());
        comms.emplace("time", make_unique<Time>());
        comms.emplace("date", make_unique<Date>());
        comms.emplace("touch", make_unique<Touch>());
        comms.emplace("truncate", make_unique<Truncate>());
        comms.emplace("truncate", make_unique<Truncate>());
        comms.emplace("rm", make_unique<Rm>());
        comms.emplace("wc", make_unique<Wc>());
        comms.emplace("tr", make_unique<Tr>());
        comms.emplace("head", make_unique<Head>());
        comms.emplace("batch", make_unique<Batch>());
    }
    return comms;
}

CLI::CLI() {
    this->m_parser = new Parser(new StdReader);
    this->m_prompt = new Prompt();
    this->m_checker = new Checker();
}

CLI::~CLI() = default;

bool CLI::containsPipes(vector<string> &comm_line) {
    for (const auto &s: comm_line) {
        if (s.front() != '"' && s.find('|') != string::npos) return true;
    }
    return false;
}

bool CLI::containsInputRedirection(vector<string> &comm_line) {
    for (const auto &s: comm_line) {
        if (s.front() != '"' && (s.find('<') != string::npos)) {
            if (s.length() == 1 && s == comm_line.back()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool CLI::containsOutputRedirection(vector<string> &comm_line) {
    for (const auto &s: comm_line) {
        if (s.front() != '"' && (s.find('>') != string::npos) || s.find(">>") != string::npos) {
            if ((s.length() == 1 || s.length() == 2) && s == comm_line.back()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

void CLI::handleMultiplePipes(vector<string>& comm_line, int& i, stack<vector<string> >& st, vector<string>& tmp) {
    if (comm_line[i].back() == '|') {
        if (!tmp.empty()) st.push(tmp);
        tmp.clear();
        string command;
        int j = comm_line[i].size() - 2;
        while (j >= 0) {
            while (j >= 0 && comm_line[i][j] != '|') {
                command = comm_line[i][j--] + command;
            }
            tmp.insert(tmp.begin(), command);
            st.push(tmp);
            tmp.clear();
            command.clear();
            j--;
        }
    } else {
        string command;
        int j = comm_line[i].size() - 1;
        while (j >= 0) {
            while (j >= 0 && comm_line[i][j] != '|') {
                command = comm_line[i][j--] + command;
            }
            tmp.insert(tmp.begin(), command);
            st.push(tmp);
            tmp.clear();
            command.clear();
            j--;
        }
    }
}

void CLI::handleSinglePipe(vector<string>& comm_line, int i, stack<vector<string> >& st, vector<string>& tmp) {
    size_t pos = comm_line[i].find('|');
    if (pos == 0) {
        tmp.insert(tmp.begin(), comm_line[i].substr(pos + 1, comm_line[i].length()));
        st.push(tmp);
        tmp.clear();
    } else if (pos == comm_line[i].length() - 1) {
        if (!tmp.empty()) st.push(tmp);
        tmp.clear();
        tmp.insert(tmp.begin(), comm_line[i].substr(0, pos));
    } else {
        string back = comm_line[i].substr(pos + 1, comm_line[i].length());
        tmp.insert(tmp.begin(), back);
        st.push(tmp);
        tmp.clear();
        string first = comm_line[i].substr(0, pos);
        tmp.insert(tmp.begin(), first);
    }
    if (i == 0) st.push(tmp);
}

stack<vector<string>> CLI::pipes(vector<string> &comm_line) {
    stack<vector<string> > st;
    vector<string> tmp;
    int i = comm_line.size() - 1;
    while (i >= 0) {
        if (comm_line[i].find('|') != string::npos) {
            if (count(comm_line[i].begin(), comm_line[i].end(), '|') > 1) {
                handleMultiplePipes(comm_line, i, st, tmp);
            } else if (comm_line[i].length() > 1) {
                handleSinglePipe(comm_line, i, st, tmp);
            } else {
                st.push(tmp);
                tmp.clear();
            }
        } else {
            tmp.insert(tmp.begin(), comm_line[i]);
            if (i == 0) st.push(tmp);
        }
        i--;
    }
    return st;
}

void CLI::handlePipes(vector<string> &comm_line) {
    stack<vector<string> > st;
    string arg;
    st = pipes(comm_line);
    vector<string> first = st.top();
    Command *first_comm = findCommand(first, "", true, "front");
    if (first_comm != nullptr) arg = '"' + first_comm->getInputStream()->read() + '"';
    else return;
    st.pop();
    while (!st.empty()) {
        vector<string> command = st.top();
        if (st.size() == 1) {
            Command *p = findCommand(command, arg, false, "rear");
        } else {
            Command *p = findCommand(command, arg, true, "middle");
            if (p == nullptr) return;
            arg = '"' + p->getInputStream()->read() + '"';
        }
        st.pop();
    }
}

InputStream* CLI::findInputStream(vector<string> &comm_line, string &arg, bool fileType) {
    if (containsInputRedirection(comm_line)) {
        string path;
        for (int i = 0; i < comm_line.size(); i++) {
            if (comm_line[i].front() != '"' && comm_line[i].find('<') != string::npos) {
                if (comm_line[i].length() == 1) {
                    path = comm_line[i + 1];
                    if (path.back() == ' ') path.pop_back();
                    if (!fs::exists(path) && path.front() != '"' && path.back() != '"') {
                        cout << "File " << path << " does not exist." << endl;
                        return nullptr;
                    }
                    return new FileInputStream(path);
                }
                if (comm_line[i].length() > 1) {
                    size_t j = comm_line[i].find('<');
                    path = comm_line[i].substr(j + 1, comm_line[i].length());
                    if (path.back() == ' ') path.pop_back();
                    if (!fs::exists(path) && path.front() != '"' && path.back() != '"') {
                        cout << "File " << path << " does not exist." << endl;
                        return nullptr;
                    }
                    return new FileInputStream(path);
                }
            }
        }
    } else {
        if (arg.front() == '"' && arg.back() == '"') return new StdInputStream(arg);
        if (!arg.empty() && arg.find('"') == string::npos) {
            if (fileType) return new StdInputStream(arg);
            if (arg.back() == ' ') arg.pop_back();
            return new FileInputStream(arg.substr(0, arg.length()));
        }
        if (arg.empty()){
            string read;

            while (arg != "EOF") {
                getline(cin, arg);
                read += arg + '\n';
            }
            read = read.substr(0, read.length() - 5);
            return new StdInputStream(read);
        }
    }
    return new StdInputStream(arg);
}

OutputStream* CLI::findOutputStream(vector<string> &comm_line) {
    if (containsOutputRedirection(comm_line)) {
        string path;
        for (int i = 0; i < comm_line.size(); i++) {
            if (comm_line[i].front() != '"' && comm_line[i].find(">>") != string::npos) {
                if (comm_line[i].length() == 2) {
                    path = comm_line[i + 1];
                    if (path.back() == ' ') path.pop_back();
                    return new FileOutputStream(path, true);
                }
                size_t j = comm_line[i].find(">>");
                path = comm_line[i].substr(j + 2, comm_line[i].length());
                if (path.back() == ' ') path.pop_back();
                if (path.front() != '"'&& path.back() != '"')
                return new FileOutputStream(path, true);
            }
            if (comm_line[i].front() != '"' && (comm_line[i].find('>') != string::npos)) {
                if (comm_line[i].length() == 1) {
                    path = comm_line[i + 1];
                    if (path.back() == ' ') path.pop_back();
                    return new FileOutputStream(path, false);
                }
                size_t j = comm_line[i].find('>');
                path = comm_line[i].substr(j + 1, comm_line[i].length());
                if (path.back() == ' ') path.pop_back();
                if (path.front() != '"'&& path.back() != '"')
                return new FileOutputStream(path, false);
            }
        }
    } else {
        return new StdOutputStream();
    }
}

void CLI::TrCase(Tr* tr, vector<string> &command, string& arg, string& comm_arg) {
    if (command.size() == 2 && arg.empty()) {
        tr->setWhat(command[1]);
        comm_arg = "";
    } else {
        if (arg.empty()) {
            if (command[1] != "<") {
                tr->setWhat(command[2]);
                if (!command[3].empty() && command[3].front() != '>') tr->setWith(command[3]);
            } else {
                tr->setWhat(command[3]);
                if (!command[4].empty() && command[4].front() != '>') tr->setWith(command[4]);
            }
        } else {
            tr->setWhat(command[1]);
            if (!command[2].empty() && command[2].front() != '>') tr->setWith(command[2]);
        }
    }
}

Command *CLI::findCommand(vector<string> &command, string arg, bool pipes, string pos) {
    string comm_arg;
    auto &comms = getCommandMap();
    const auto i = comms.find(command[0]);

    if (i != comms.end()) {
        if (i->second->hasArgument()) {
            if (i->second->hasOption()) {
                i->second->setOption(command[1]);
                comm_arg = !arg.empty() ? arg : command[2];
                i->second->isFileType() ? i->second->setInputStream(findInputStream(command, comm_arg, true)) : i->second->setInputStream(findInputStream(command, comm_arg, false));
                if (!i->second->getInputStream()) return nullptr;
                i->second->setOutputStream(findOutputStream(command));
            } else {
                comm_arg = !arg.empty() ? arg : command[1];
                if (Tr *tr = dynamic_cast<Tr *>(i->second.get())) TrCase(tr, command, arg, comm_arg);
                i->second->isFileType() ? i->second->setInputStream(findInputStream(command, comm_arg, true)) : i->second->setInputStream(findInputStream(command, comm_arg, false));
                if (!i->second->getInputStream()) return nullptr;
                i->second->setOutputStream(findOutputStream(command));
            }
        } else {
            i->second->setOutputStream(findOutputStream(command));
        }
        i->second->slice();

        if (Prompt *p = dynamic_cast<Prompt *>(i->second.get())) p->setCLI(this);
        if (Batch *b = dynamic_cast<Batch *>(i->second.get())) b->setCLI(this);

        if (this->m_checker->checkErrors(i->second.get(), command, pipes, pos))
            i->second->execute(pipes);
        else return nullptr;

    } else {
        cout << "Unknown command: " << command[0];
        return nullptr;
    }
    return i->second.get();
}

bool CLI::nextCommand() {
    vector<string> comm_line;
    comm_line = this->m_parser->parseLine();

    if (comm_line.empty()) {
        cout << "END" << endl;
        return false;
    }
    if (containsPipes(comm_line)) {
        handlePipes(comm_line);
    } else {
        Command *c = findCommand(comm_line, "", false, "middle");
    }
    cout << endl;
    return true;
}

void CLI::displayPrompt() const {
    cout << this->m_prompt->getPrompt();
}
