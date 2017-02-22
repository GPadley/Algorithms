#include <iostream>

using namespace std;

struct intlist {
    int val;
    intlist* next;
};

int main(){

    intlist* l = NULL;

    int n, el;

    cout << "How many elements?" << endl;

    cin >> n;

    for(int i = 0; i < n; i++){

        cout << "Enter elements " << i+1 << endl;

        cin >> el;

        intlist* tmp = new intlist;

        tmp->val = el;

        tmp->next = l;

        l = tmp;

    }

    cout << endl;

    intlist* lit = l;

    while(lit!=NULL){
        cout << lit->val << endl;
        lit = lit->next;

    }

}
