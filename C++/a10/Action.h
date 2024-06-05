#pragma once
#include <iostream>
#include <Dog.h>
#include <vector>
#include "VirtualRepo.h"
#include "Repository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "TextRepository.h"
using namespace std;

class Action {
protected:
    VirtualRepo& repo;
    Dog dog;

public:
    Action(VirtualRepo& repo, const Dog& dog) : repo(repo), dog(dog) {}
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Action() = default;
};


