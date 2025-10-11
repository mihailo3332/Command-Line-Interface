//
// Created by Mihailo Mitrovic on 13. 7. 2025..
//
#include "../header files/Stream.h"

#include <iostream>

InputStream::InputStream() = default;

InputStream::~InputStream() = default;

OutputStream::OutputStream() = default;

OutputStream::~OutputStream() = default;

StdInputStream::StdInputStream(string &arg) {
    if (arg.front() == '"' && arg.back() == '"')
        this->argument = arg.substr(1, arg.length() - 2);
    else
        this->argument = arg;
}

StdInputStream::~StdInputStream() = default;

string StdInputStream::read() {
    return this->argument;
}

FileInputStream::FileInputStream(const string &filepath) {
    this->inputFile = new ifstream(filepath);
}

FileInputStream::~FileInputStream() {
    this->inputFile->close();
    delete this->inputFile;
}

string FileInputStream::read() {
    if (this->inputFile->is_open()) {
        this->inputFile->seekg(0, ios::beg);
        ostringstream ss;
        ss << this->inputFile->rdbuf();
        string line = ss.str();
        if (line.back() == '\n') line.pop_back();
        return line;
    }
    cout << "Error while opening a file.";
    return "";
}

StdOutputStream::StdOutputStream() = default;

StdOutputStream::~StdOutputStream() = default;

void StdOutputStream::write(const string &str) {
    cout << str;
}

FileOutputStream::FileOutputStream(const string &filepath, bool append) {
    if (fs::exists(filepath)) {
        if (append) {
            this->outputFile = new ofstream(filepath, ios_base::app);
        } else {
            this->outputFile = new ofstream(filepath, ios_base::trunc);
        }
    } else {
        this->outputFile = new ofstream(filepath);
    }
}

FileOutputStream::~FileOutputStream() {
    this->outputFile->close();
    delete this->outputFile;
}

bool FileOutputStream::getIsDoubleRedirection() const {
    return this->isDoubleRedirection;
}

void FileOutputStream::setDoubleRedirection() {
    this->isDoubleRedirection = true;
}

void FileOutputStream::write(const string &str) {
    if (this->outputFile->is_open()) {
        *this->outputFile << str;
        this->outputFile->close();
    }
}
