//
// Created by Mihailo Mitrovic on 6. 7. 2025..
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include "../header files/Stream.h"

using namespace std;

class Command {
  public:

    Command();

    virtual ~Command();

    string getName() const;

    string getArgument() const;

    string getOption() const;

    int getNumberOfParams() const;

    virtual void execute(bool pipes) = 0;

    virtual bool hasOption() const;

    virtual bool hasArgument() const;

    virtual bool isFileType() const;

    InputStream* getInputStream() const;

    OutputStream* getOutputStream() const;

    void setOption(const string& option);

    void setArgument(const string& argument);

    void setInputStream(InputStream* inputStream);

    void setOutputStream(OutputStream* outputStream);

    void slice();

   protected:

     string comm_name;
     string comm_option;
     string comm_argument;
     InputStream* in_stream = nullptr;
     OutputStream* out_stream = nullptr;
     int numberOfParams = 0;

};

#endif //COMMAND_H
