#include <iostream>
#include "managerUI.h"
#include "crtdbg.h"

using namespace std;



/*
    #ADDD Choose Mode
    Administrator mode: 
        - Add dog                         |
        - Delete DOG [WHEN IS ADOPTED]    |    MANAGE DOGS
        - Update info of a dog            |
        - Show all dogs

    User mode:
        - Seen dogs one by one. IF goees to the end of array, then he restart and goes from 1;
        For each dog showed:
            - Adopt a dog [Add to the user's adoption list]
            - Not adopt dog. Next dog!
        - See all dogs of a given breed, age < age_given | breed==NULL -> All dogs
        - See the adoption list

    

    DOG MODEL:
        - breed
        - name
        - age
        - photograph [link with photos]

    ADOPTION MODEL:
        - user
        - dog[DOG CLASS]

    REPOSITORY:
        - adoption_list [DynamicArray adoption class]
        - dog_list [DynamicArray Dog class]
*/


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    cout << "TODO: Provide tests and specifications for non-trivial functions outside the UI. Test coverage must be at least 98% for all layers, except the UI." << endl << endl;


    managerUI ui = managerUI();
    int disconnected = 0;
    while (disconnected == 0) {
        disconnected = ui.startUI();
    }
    

    _CrtDumpMemoryLeaks;
    return 0;
}