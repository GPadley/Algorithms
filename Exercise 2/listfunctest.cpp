#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef int list_age;
typedef string list_name;
struct listnode{
    list_age val;
    list_name name;
    listnode* next;
};

typedef listnode* mlist;

void consref(list_age el, list_name en, mlist& l);
void printlist(mlist l);
void deallocatec(mlist l);
void ListDelete(mlist& l, int value, bool& found);

int main(){
    fstream infile;
    mlist la = NULL;
    int n;
    bool found;

    list_age el;
    list_name en;

    infile.open("list.txt");
    if(!infile.is_open()){
        cout << "Could not open input file" << endl;
        exit(EXIT_FAILURE);
    }

    while(infile >> en && infile >> el){
        consref(el, en, la);
    }
    infile.close();

    cout << endl;

    printlist(la);

    cout << endl << "Enter a value to delete" << endl;
    cin >> n;

    ListDelete(la, n, found);
    if(found == true){
        cout << endl << "New list is:" << endl;
        printlist(la);
    }
    else{
        cout << "List is unchanged" << endl;
    }
    deallocatec(la);

    return 0;
}

void consref(list_age el, list_name en, mlist& l){
    mlist tmpp = new listnode;
    tmpp->val = el;
    tmpp->name = en;
    tmpp->next = l;
    l = tmpp;
}

void printlist(mlist l){
    while (l != NULL){
        cout << l->name << " is " << l->val << " years old." << endl;
        l = l->next;
    }
}

void deallocatec(mlist l){
    while (l != NULL){
        mlist nextl = l->next;
        delete l;
        l = nextl;
    }
}

void ListDelete(mlist& l, int value, bool& found){
    found = false;

    while(l != NULL){
        if (l->val == value) {
            cout << "yes" << endl;
            mlist k = l->next;
            found = true;
            delete l;
            l = k;
        }
        else{
            cout << "nope" << endl;
            l = l->next;
        }
    }
}
