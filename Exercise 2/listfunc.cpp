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
mlist consret(list_age el, list_name en, mlist l);
void printlist(mlist l);
void deallocatec(mlist l);
void deallocater(mlist& l);

int main(){
    fstream infile;
    mlist la = NULL;

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

    cout << endl;

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
