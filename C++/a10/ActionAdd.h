#pragma once
#include "Action.h"
class ActionAdd : public Action
{
public:
    ActionAdd(VirtualRepo& repo, const Dog& dog) : Action{ repo,dog } {}
    ~ActionAdd() {}
    void execute() override {
        repo.addDog(dog);
    }

    void undo() override {
        if (dog.getAdopted())
            repo.deleteAddoptedDog(dog);
        else
            repo.deleteDog(dog);
    }
};

