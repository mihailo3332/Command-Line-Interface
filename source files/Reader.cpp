//
// Created by Mihailo Mitrovic on 13. 7. 2025..
//

#include "../header files/Reader.h"

Reader::Reader() = default;

Reader::~Reader() = default;

StdReader::StdReader() = default;

StdReader::~StdReader() = default;

string StdReader::readLine() const {
    string line;
    getline(cin, line);
    return line;
}

bool StdReader::endOfRead() const {
    return cin.eof();
}

FileReader::FileReader(const string &filepath) {
    input_file = new ifstream(filepath);
}

FileReader::~FileReader() {
    input_file->close();
    delete input_file;
}

string FileReader::readLine() const {
    string line;
    getline(*input_file, line);
    return line;
}

bool FileReader::endOfRead() const {
    return input_file->eof();
}
