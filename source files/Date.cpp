//
// Created by Mihailo Mitrovic on 9. 8. 2025..
//
#include "../header files/Date.h"

Date::Date() {
    this->comm_name = "date";
    this->numberOfParams = 1;
}

Date::~Date() = default;

bool Date::hasOption() const {
    return false;
}

bool Date::hasArgument() const {
    return false;
}

bool Date::isFileType() const {
    return false;
}

void Date::execute(bool pipes) {
    time_t timestamp = time(nullptr);
    tm datetime;

#ifdef __APPLE__
    localtime_r(&timestamp, &datetime);
#elif __WIN32
    localtime_s(&datetime, &timestamp);
#endif

    string res = to_string(datetime.tm_mday) + "." + to_string(1 + datetime.tm_mon) + "." + to_string(
                     datetime.tm_year + 1900) + ".";

    this->setInputStream(new StdInputStream(res));

    if (!pipes)this->getOutputStream()->write(res);
}
