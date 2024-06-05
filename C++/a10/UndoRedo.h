#pragma once

#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"
#include "ActionUpdate.h"
#include <vector>
#include <iostream>


using namespace std;
class UndoRedo
{
private:
    vector<unique_ptr<Action>> undolist;
    vector<unique_ptr<Action>> redolist;

public:
    UndoRedo() = default;
    UndoRedo(const UndoRedo&) = delete; // Dezactivează copierea
    void executeCommand(unique_ptr<Action> command) {
        undolist.push_back(move(command));
        redolist.clear();
    }

   void undo() {
        if (!undolist.empty()) {
            unique_ptr<Action> comm = move(undolist.back());
            undolist.pop_back();
            comm->undo();
            redolist.push_back(move(comm));
        }
        else {
            throw exception("No undos avalible!");
        }
    }

    void redo() {
        try
        {
            if (redolist.size() > 0 && !redolist.empty()) {
                unique_ptr<Action> comm = move(redolist.back());
                redolist.pop_back();
                comm->execute();
                undolist.push_back(move(comm));
            }
            else {
                throw exception("No redos avalible!");
            }
        }
        catch (const std::exception&)
        {
            throw exception("No redos avalible!");
        }
        
    }

};

