#include "LMOMS.h"
#include <fstream>

using namespace std;

int main() {
    LMOMS OB;

    string line;
    ifstream myfile ("/Users/siddharthmehrotra/CLionProjects/LimitMarketOrderManagementSystem/test/in.txt");

    if (myfile.is_open()) {
        while ( getline(myfile,line) ) {
            OB.execute_order(line);
//            cout << OB.execute_order(line).str(); // verbose execution
//            OB.print_order_book();
        }
        OB.print_order_book();
        myfile.close();
    }
    else
        cout << "Unable to open file";
    return 0;
}
