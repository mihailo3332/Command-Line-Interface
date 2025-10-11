//
// Created by Mihailo Mitrovic on 31. 7. 2025..
//
#include "../header files/Time.h"

Time::Time() {
    this->comm_name = "time";
    this->numberOfParams = 1;
}

Time::~Time() = default;

bool Time::hasOption() const {
    return false;
}

bool Time::hasArgument() const {
    return false;
}

bool Time::isFileType() const {
    return false;
}

void Time::execute(bool pipes) {
    time_t timestamp = time(nullptr);
    tm datetime;

#ifdef __APPLE__
    localtime_r(&timestamp, &datetime);
#elif __WIN32
    localtime_s(&datetime, &timestamp);
#endif

    string res = to_string(datetime.tm_hour) + ":" + to_string(datetime.tm_min) + ":" + to_string(datetime.tm_sec);

    this->setInputStream(new StdInputStream(res));

    if (!pipes) this->getOutputStream()->write(res);
}
