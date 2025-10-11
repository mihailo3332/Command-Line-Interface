//
// Created by Mihailo Mitrovic on 17. 7. 2025..
//

#ifndef PROMPT_H
#define PROMPT_H
#include "CLI.h"
#include "Command.h"
using namespace std;

class Prompt : public Command  {
  public:

    Prompt();

    ~Prompt() override;

    void setCLI(CLI* cli);

    string getPrompt() const;

    void setPrompt(string& pr);

    bool hasOption() const override;

    bool hasArgument() const override;

    bool isFileType() const override;

    void execute(bool pipes) override;

  private:
      CLI* m_cli = nullptr;
      string prompt = "$";
};




#endif //PROMPT_H
