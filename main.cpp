#include "LM_OMS.h"
#include <fstream>

int main() {
    LM_OMS OB;

    string line;
    ifstream myfile ("/Users/siddharthmehrotra/Library/Mobile Documents/com~apple~CloudDocs/Scientific C++/LHFT/cmake-build-debug/in1.txt");

    if (myfile.is_open()) {
        while ( getline(myfile,line) ){
            OB.execute_order(line);
//            cout << OB.execute_order(line).str(); // verbose execution
        }
        OB.print_order_book();
        myfile.close();
    }
    else cout << "Unable to open file";
    return 0;
}
