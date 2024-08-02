#include <exception>
#include <string>
#ifndef DATE_H
#define DATE_H

class FaultyInput : public std::exception {
    private: 
        std::string message; 
    
    public:
        FaultyInput(const char* msg) : message(msg) {} 
        const char* what() const throw() 
        { 
            return message.c_str(); 
        } 
};

#endif