#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

struct myException : std::exception {
    myException(char* a): a_(a){};
    const char* what() const noexcept {return a_;}
private:
    char* a_;
};

#endif