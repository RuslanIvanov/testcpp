$ g++ --version
g++ (Ubuntu 4.8.5-2ubuntu1~14.04.1) 4.8.5
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ g++ --std=c++11 -o test test.cpp
$ ./test
std::stoi("45") is 45
std::stoi("3.14159") is 3
std::stoi("31337 with words") is 31337
