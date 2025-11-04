#include <iostream>
#include "CNumber.h"
using namespace std;


int main() {

    // automatyczne sprawdzanie wycieków po zakończeniu programu
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

   
    CNumber a, b, res;


    a = 91234567;
    b = 14532;
    res = b^a;
    res.printInfo();
    return 0;
}
