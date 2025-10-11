//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#ifndef CLI_H
#define CLI_H
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>
#include <sstream>
#include "Command.h"
#include "Echo.h"
#include "Parser.h"
#include "Time.h"
#include "Date.h"
#include "Touch.h"
#include "Truncate.h"
#include "Rm.h"
#include "Wc.h"
#include "Tr.h"
#include "Head.h"
#include "Stream.h"
#include "Checker.h"

using namespace std;
class Prompt;
class Batch;

class CLI {
  public:

    CLI();

    ~CLI();

    bool nextCommand();

    void displayPrompt() const;

    friend class Prompt;

    friend class Batch;

    static bool containsPipes(vector<string>& comm_line);

    static bool containsInputRedirection(vector<string>& comm_line);

    static bool containsOutputRedirection(vector<string>& comm_line);

private:
    Parser* m_parser;
    Prompt* m_prompt;
    Checker* m_checker;

    Command* findCommand(vector<string>& command, string arg, bool pipes, string pos);

    static InputStream* findInputStream(vector<string>& comm_line, string& arg, bool fileType);
    static OutputStream* findOutputStream(vector<string>& comm_line);

    static stack<vector<string>> pipes(vector<string>& comm_line);
    void handlePipes(vector<string>& comm_line);
    static void handleMultiplePipes(vector<string>& comm_line, int& i, stack<vector<string> >& st, vector<string>& tmp);
    static void handleSinglePipe(vector<string>& comm_line, int i, stack<vector<string> >& st, vector<string>& tmp);

    static void TrCase(Tr* tr, vector<string> &command, string& arg, string& comm_arg);
};

#endif //CLI_H
