#pragma once
#include <iostream>

using namespace std;
class Exceptions : public std::exception {
private:
    std::string message;
public:

    Exceptions() {};
    const char* what() const noexcept override {
        return message.c_str();
    }

    Exceptions invalidInput() {
        Exceptions ex;
        ex.message = "Invalid Input!";
        return ex;
    }

    Exceptions invalidAge() {
        Exceptions ex;
        ex.message = "Invalid Age! Needs to be between 0-99.";
        return ex;
    }

    Exceptions dogNotExist() {
        Exceptions ex;  
        ex.message = "This dog doesn't exist!";
        return ex;
    }


    Exceptions dogExist() {
        Exceptions ex;
        ex.message = "This dog already exist!";
        return ex;
    }

    Exceptions dogsNotFound() {
        Exceptions ex;
        ex.message = "List with dogs is empty.";
        return ex;
    }

    Exceptions dogNotAddopted() {
        Exceptions ex;
        ex.message = "This dog isn't addopted..";
        return ex;
    }

    Exceptions dogAddoptedNotUpdate() {
        Exceptions ex;
        ex.message = "This dog is addopted. You can't update";
        return ex;
    }

    Exceptions objectNULL() {
        Exceptions ex;
        ex.message = "Object NULL pointer.";
        return ex;
    }

    Exceptions invalidBreedName() {
        Exceptions ex;
        ex.message = "Invalid breed or name.";
        return ex;
    }

    Exceptions invalidIndex() {
        Exceptions ex;
        ex.message = "Invalid index.";
        return ex;
    }
    
};

