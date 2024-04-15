#include <iostream>
#include "managerUI.h"
#include "crtdbg.h"
#include "tests.h"
#include "TextRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "MongoDB.h"

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


bool fileFound(string filename) {
    ifstream in(filename);
    return in.is_open();
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    {

        //callTests();
        bool repositoryCreate = false;
        VirtualRepo* repository = NULL;
        while (!repositoryCreate) {
            string option;
            cout << " Choose Repository \n";
            cout << "1. Memory\n";
            cout << "2. File\n";
            cout << "3. CSV \n";
            cout << "4. HTML \n";
            cout << "5. MYSQL \n";
            try
            {
                getline(cin, option);
                int optionInt = stoi(option);
                string filename;
                string filenameparticulary;
                switch (optionInt)
                {
                case 1:
                    cout << "Memory " << endl;
                    repositoryCreate = true;
                    repository = new Repository();
                    break;
                case 2:
                    cout << "File " << endl;
                    repositoryCreate = true;
                    cout << "Type file name: ";
                    getline(cin, filename);
                    while (!fileFound(filename)) {
                        cout << "Type file name[TXT]: ";
                        getline(cin, filename);
                    }

                    repository = new TextRepository(filename);
                    break;
                case 3:
                    cout << "CSV " << endl;
                    repositoryCreate = true;
                    cout << "Type file name[TXT]: ";
                    getline(cin, filename);
                    while (!fileFound(filename)) {
                        cout << "Type file name[TXT]: ";
                        getline(cin, filename);
                    }

                    while (!fileFound(filenameparticulary)) {
                        cout << "Type file name[CSV]: ";
                        getline(cin, filenameparticulary);
                    }

                    repository = new CSVRepository(filename, filenameparticulary);
                    break;
                case 4:
                    cout << "HTML " << endl;
                    repositoryCreate = true;
                    cout << "Type file name[TXT]: ";
                    getline(cin, filename);
                    while (!fileFound(filename)) {
                        cout << "Type file name[TXT]: ";
                        getline(cin, filename);
                    }

                    while (!fileFound(filenameparticulary)) {
                        cout << "Type file name[HTML]: ";
                        getline(cin, filenameparticulary);
                    }

                    repository = new HTMLRepository(filename, filenameparticulary);
                    break;
                case 5:
                    cout << "MYSQL " << endl;
                    repositoryCreate = true;
                    repository = new MongoDB();
                    break;
                default:
                    cout << "Wrong Option! Try again! \n";
                    break;
                }
            }
            catch (const std::exception&)
            {
                cout << "Wrong Option! Try again! \n";
            }
            
        }

        Service service{ repository };
        managerUI ui{ service };
        int disconnected = 0;
        while (disconnected == 0) {
            disconnected = ui.startUI();
        }
        delete repository;
    }
    _CrtDumpMemoryLeaks();
    return 0;
}