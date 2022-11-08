#include <iostream>
#include "lib1.h"

// add 1111111111111
// add 222222222222
// add 333333333333
int main(int argc, char** argv) {
    int cc= 20;
    std::cout << "Hello, world!\n";

#ifdef LIB1
    printLib(cc);
#else
    PrintLib2(122);
#endif
}
