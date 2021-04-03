#ifndef __EXCEPTIONS_H_
#define __EXCEPTIONS_H_

#include<exception>
#include<string>
#include<sstream>

class NotPythonTranslateable : public std::exception {
    public:
        const char* constructName;

    
        NotPythonTranslateable(const char* _constructName)
            : constructName(_constructName) {};

        virtual const char* what() const noexcept override {
            std::stringstream ss;
            ss << constructName << " is not translateable to python";
            return ss.str().c_str();
        }
};

#endif // __EXCEPTIONS_H_
