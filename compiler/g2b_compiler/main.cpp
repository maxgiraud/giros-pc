#include <iostream>
#include <sstream>
#include <fstream>

#include "compiler.h"

using namespace std;


int main(int argc, char** argv) {

    if (argc == 2) {
    
        Compiler comp(argv[1]);

        int error = comp.Run();

    } else {

        cout << "Error\n";
    }

    return 0;
}
