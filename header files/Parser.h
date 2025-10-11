//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#ifndef PARSER_H
#define PARSER_H
#include "Reader.h"
#include <string>
#include <vector>
using namespace std;

class Parser {
  public:

    Parser(Reader *reader);

    ~Parser();

    vector<string> parseLine();

    static vector<string> parse(string& line);

   private:

      Reader *m_reader;
};

#endif //PARSER_H
