#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#define ASIZE 3;

using namespace std;

struct intlist {
    int val;
    intlist* next;
};

int main(){
    intlist* l = NULL;

    int e1, n = 0;
    string filename;
    ifstream infile;
    cout << "Enter the name of the file" << endl;
    cin >> filename;
    infile.open(filename.c_str());
    if(!infile.is_open()){
        cout << "Could not open input file" << endl;
        exit(EXIT_FAILURE);
    }

    while(infile >> e1){
            intlist* tmp = new intlist;

            tmp->val = e1;
            tmp->next = l;
            l = tmp;
    }
    infile.close();

    cout << endl;
    intlist* lit = l;

    while(lit != NULL){
        cout << lit->val << endl;
        lit = lit->next;
        n++;
    }
    cout << endl << "The number of items in this list is " << n << endl;
    while(l != NULL){
        intlist* tmp1 = l->next;
        delete l;
        l = tmp1;
    }

    return 0;
}
