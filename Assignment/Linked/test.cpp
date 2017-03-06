#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    // Check the number of parameters
    if (argc < 2) {
        // Tell the user how to run the program
        cout << "Usage: " << argv[0] << " NAME" << endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
    // Print the user's name:
    cout << argv[0] << " says hello, " << argv[1] << "!" << endl;
    return 0;
}
