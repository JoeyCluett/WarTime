/*

    This is a companion program to Surround. This program 
    assists in the creation of maps for use on Surround. 
    Every map contains 10,000 arranged in a 100x100 grid

    A map name and a command are passed to the program. This 
    means it is up to the developer to not accidently overwrite 
    existing maps

    I'd eventually like the program to support 

*/

#include <iostream>
#include <SDL/SDL.h>

using namespace std;

int main(int argc, char* argv[]) {

    if(argc < 2) {
        cout << "Please supply a map name to create/modify\n";
        exit(1);
    }

    

    return 0;
}
