//
// Created by Mihailo Mitrovic on 11. 7. 2025..
//

#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Reader {
  public:

    Reader();

    virtual ~Reader();

    virtual string readLine() const = 0;

    virtual bool endOfRead() const = 0;

};

class StdReader : public Reader {
  public:

    StdReader();

    ~StdReader() override;

    string readLine() const override;

    bool endOfRead() const override;

};

class FileReader : public Reader {
  public:

    FileReader(const string& filepath);

    ~FileReader() override;

    string readLine() const override;

    bool endOfRead() const override;

  private:

    ifstream* input_file{};

};

#endif //READER_H
