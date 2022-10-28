#include <iostream>
#include "lib1.h"





int main(int argc, char** argv) {
    int cc= 20;
    std::cout << "Hello, world!\n";

#ifdef LIB1
    printLib(cc);
#else
    PrintLib2(122);
#endif
}
