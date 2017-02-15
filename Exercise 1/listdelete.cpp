#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

struct intlist {
    int val;
    intlist* next;
};

intlist *ListDelete(intlist *currP, int value, bool& found);
void printlist(intlist* list);

int main(){
    intlist* l = NULL;

    int e1, value;
    bool found;
    ifstream infile;
    infile.open("list.txt");
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

    cout << "Input what number you would like to remove" << endl;
    cin >> value;

    cout << endl;

    l = ListDelete(l, value, found);

    intlist* out = l;
    if(found == false){
        cout << value << " wasn't found" << endl;
        cout << "Original list was:" << endl;
        printlist(out);
    }

    if(found == true){
        cout << value << " was found" << endl;
        cout << "New list is:" << endl;
        printlist(l);
    }

    while(l != NULL){
        intlist* tmp1 = l->next;
        delete l;
        l = tmp1;
    }

    return 0;
}

intlist *ListDelete(intlist *currP, int value, bool& found)
{
    found = false;
  /* See if we are at end of list. */
  if (currP == NULL)
    return NULL;

  /*
   * Check to see if current node is one
   * to be deleted.
   */
  if (currP->val == value) {
    intlist *tempNextP;
    found = true;
    /* Save the next pointer in the node. */
    tempNextP = currP->next;

    /* Deallocate the node. */
    delete(currP);

    /*
     * Return the NEW pointer to where we
     * were called from.  I.e., the pointer
     * the previous call will use to "skip
     * over" the removed node.
     */
    return tempNextP;
  }

  /*
   * Check the rest of the list, fixing the next
   * pointer in case the next node is the one
   * removed.
   */
  currP->next = ListDelete(currP->next, value, found);


  /*
   * Return the pointer to where we were called
   * from.  Since we did not remove this node it
   * will be the same.
   */
  return currP;
}

void printlist(intlist* list){

    while(list != NULL){
        cout << list->val << endl;
        list = list->next;
    }

}
