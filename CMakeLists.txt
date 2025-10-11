cmake_minimum_required(VERSION 3.30)
project(OOP_Projekat)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOP_Projekat main.cpp
        "source files/Command.cpp"
        "source files/Echo.cpp"
        "source files/CLI.cpp"
        "source files/Reader.cpp"
        "source files/Parser.cpp"
        "source files/Stream.cpp"
        "source files/Prompt.cpp"
        "source files/Time.cpp"
        "source files/Date.cpp"
        "source files/Touch.cpp"
        "source files/Truncate.cpp"
        "source files/Rm.cpp"
        "source files/Wc.cpp"
        "source files/Tr.cpp"
        "source files/Head.cpp"
        "source files/Batch.cpp"
        "source files/Checker.cpp")
