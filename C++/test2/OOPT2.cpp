#include <iostream>
#include "uiManager.h"
#include <crtdbg.h>
using namespace std;

int main()
{
	{
		Service srv{};
		uiManager ui{ srv };
		ui.start();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

