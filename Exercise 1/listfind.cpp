#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

struct intlist {
    int val;
    intlist* next;
};

int main(){
    intlist* l = NULL;

    int e1, n = 0, value;
    bool found = false;
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

    cout << "Input what number you would like to find" << endl;
    cin >> value;

    cout << endl;
    intlist* lit = l;

    while(lit != NULL){
        n++;
        if(lit->val == value){
            cout << lit->val << " is item " << n << " in the list" <<endl;
            found = true;
        }
        lit = lit->next;
    }
    if(found == false){
        cout << value << " wasn't found" << endl;
    }

    while(l != NULL){
        intlist* tmp1 = l->next;
        delete l;
        l = tmp1;
    }

    return 0;
}
