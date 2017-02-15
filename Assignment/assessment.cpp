#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


using namespace std;

struct intlist {
	int val;
	intlist* next;
};

typedef intlist* mlist;

void insert_int(int value, intlist*& l);
void rev_list(intlist*& l);
void print_list(intlist* l);
intlist *delete_val(intlist *currP, int value);
int main(){

	intlist* list = NULL; //clear linked list

	string cmd, cmdfile, intfile, fnum; //file input strings
	int val;
	ifstream infile1, infile2;
	ofstream outfile;
	cout << "Input the name of the file commands" << endl;

	cin >> cmdfile;

	infile1.open(cmdfile.c_str());

	if(!infile1.is_open()){

		cout << "Could not open input file" << endl;
		exit(EXIT_FAILURE);

	}

	while(infile1 >> cmd){

		if(cmd == "r"){

			infile1 >> fnum;
			intfile = "data_" + fnum + ".txt";

			infile2.open(intfile.c_str());

				if(!infile2.is_open()){

					cout << "Could not open input file" << endl;
					exit(EXIT_FAILURE);

					}

			while(infile2 >> val){
				insert_int(val, list);
				}
				rev_list(list);
				print_list(list);
				infile2.close();

		}

		else if(cmd == "s"){

		}

		else if(cmd == "w"){
			infile1 >> fnum;
			intfile = "outfile_" + fnum + ".txt";

			outfile.open(intfile.c_str(), ofstream::out | ostream::app);

			while(list != NULL){
				outfile << list->val << endl;
				list = list->next;
			}
			outfile.close();

		}

		else if(cmd == "i"){

		}

		else if(cmd == "d"){
			int del;
			infile1 >> del;
			delete_val(list, del);
			cout << "exit" << endl;
			print_list(list);
		}

		else if(cmd == "e"){

		}

	}


return 0;

}

void insert_int(int value, intlist*& l){

	intlist* tmp = new intlist;
	tmp->val = value;
	tmp->next = l;
	l = tmp;
}

void print_list(intlist* l){
	while(l != NULL){
		cout << l->val << endl;
		l = l->next;
	}
}

void rev_list(intlist*& l){
		intlist* tmp = NULL;//creates new list
		intlist* current = l;
		intlist* next;
	while(current != NULL){
		next  = current->next;
        current->next = tmp;
        tmp = current;
        current = next;
	}

	l = tmp;
}

// void delete_val(intlist*& l, int delval){
// 	bool found = false;
// 	intlist* tmp = new intlist;
// 	print_list(l);
// 	while(l != NULL){
// 		if(l->val == delval && found == false){
// 			cout << "found val" << endl;
//
// 			delete l;
// 			l = tmp;
// 		}
// 		else{
// 			tmp = l;
// 			l = l->next;
// 		}
// 	}
// }

intlist *delete_val(intlist *currP, int value){

  	if (currP == NULL)
    	return NULL;

  	if (currP->val == value) {
    	intlist *tempNextP;
    	tempNextP = currP->next;

    	delete(currP);

    	return tempNextP;
  	}

  	currP->next = delete_val(currP->next, value);

  	return currP;
}
