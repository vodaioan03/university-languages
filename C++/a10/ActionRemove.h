#pragma once
#include "Action.h"
class ActionRemove: public Action
{
public:
    ActionRemove(VirtualRepo& repo, const Dog& dog) : Action{ repo, dog } {}
    ~ActionRemove() {}
    void execute() override {
       repo.deleteAddoptedDog(dog);
    }

    void undo() override {
        repo.addDog(dog);
        repo.addoptDog(dog.getName(), dog.getBreed());
    }
};

