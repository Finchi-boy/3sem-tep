#include <iostream>
#include "CNumber.h"

using namespace std;



int main()
{
	// automatyczne sprawdzanie wycieków po zakoñczeniu programu
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



    CNumber c1;
    CNumber c2;
    c1 = 90060;
    c2= 15;
    c1 = c1/c2;
    c1.printInfo();
    

    
    return 0;
}


