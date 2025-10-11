//
// Created by Mihailo Mitrovic on 13. 7. 2025..
//

#ifndef STREAM_H
#define STREAM_H

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

class InputStream {
  public:

    InputStream();

    virtual ~InputStream();

    virtual string read() = 0;

};

class StdInputStream : public InputStream {
  public:

    StdInputStream(string& arg);

    ~StdInputStream() override;

     string read() override;

  private:
  string argument;
};

class FileInputStream : public InputStream {
  public:

    FileInputStream(const string &filepath);

    ~FileInputStream() override;

    string read() override;

  private:
  ifstream* inputFile;

};

class OutputStream {
  public:

    OutputStream();

    virtual ~OutputStream();

    virtual void write(const string &str) = 0;
};

class StdOutputStream : public OutputStream {
  public:

    StdOutputStream();

    ~StdOutputStream() override;

     void write(const string &str) override;

};

class FileOutputStream : public OutputStream {
  public:

    FileOutputStream(const string &filepath, bool append);

    ~FileOutputStream() override;

    bool getIsDoubleRedirection() const;

    void setDoubleRedirection();

    void write(const string &str) override;

  private:
  ofstream* outputFile;
  bool isDoubleRedirection = false;

};


#endif //STREAM_H
