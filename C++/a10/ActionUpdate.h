#pragma once
#include "Action.h"
class ActionUpdate : public Action
{
private:
    Dog newDog;

public:
    ActionUpdate(VirtualRepo& repo, const Dog& dog, const Dog& newDog) : Action{repo, dog}, newDog{ newDog } {}
    ~ActionUpdate() {}
    void execute() override {
        repo.updateDog(dog.getName(),dog.getBreed(), newDog.getName(), newDog.getBreed(), newDog.getAge(), newDog.getPhotograph());
    }

    void undo() override {
        repo.updateDog(newDog.getName(),newDog.getBreed(), dog.getName(), dog.getBreed(), dog.getAge(), dog.getPhotograph());
    }
};

