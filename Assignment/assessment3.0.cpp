#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


using namespace std;

struct intlist{
	int val;
	intlist* next;
};

typedef intlist* mlist;

void insert_int(intlist*& l, int value); //function to add integer to start of list
void rev_list(intlist*& l); //reverse list to have in correct order
void print_list(intlist* l); //prints list to be able to view output
void delete_val(intlist*& l, int value); //delete function
void num_even(intlist* l, int& tot); //sees how many numbers are even
void bubble_sort(intlist*& l, bool& nochange); //bubble sort algorithm
void insert_end(intlist*& l, int value); //insterting value if bubble sort hasn't been executed
void insert_sort(intlist*& l, int value); //insterting value if bubble sort has been executed

int main(int argc, char* argv[]){

	intlist* list = NULL; //empty linked list
	string cmd, cmdfile, intfile, fnum; //file input strings
	int val; //input for list
	bool sorted = false; //to know whether list has been sorted or not
	ifstream infile1, infile2; //input stream
	ofstream outfile; //output stream

	if(argc < 2){
		cout << "Input the name of the file commands" << endl;
		cin >> cmdfile;
	}
	else{
		cmdfile = argv[1];
	}

	infile1.open(cmdfile.c_str()); //
	if(!infile1.is_open()){

		cout << "Could not open input file" << endl;
		exit(EXIT_FAILURE); //if the file cannot be opened, exit script

	}

	while(infile1 >> cmd){
		//read file input
		if(cmd == "r"){

			infile1 >> fnum;
			intfile = "data_" + fnum + ".txt";
			infile2.open(intfile.c_str());

			if(!infile2.is_open()){
				cout << "Could not open input file" << endl;
				exit(EXIT_FAILURE);

			}
			intfile = "output_" + fnum + ".txt";
			outfile.open(intfile.c_str(), ofstream::out | ostream::app);
			sorted = false; //resets the boolean telling whether the bubble sort has been executed
			while(infile2 >> val){
				insert_int(list, val);
			}

			rev_list(list);
			infile2.close();

		}
		//bubble sort input
		else if(cmd == "s"){
			bubble_sort(list, sorted);
		}
		//write to file input
		else if(cmd == "w"){
			intlist* outlist = list;
			while(outlist != NULL){
				outfile << outlist->val << endl;
				outlist = outlist->next;
			}

		}
		//insert into list function
		else if(cmd == "i"){
			int insert;
			infile1 >> insert;
			if(sorted == false){
				insert_end(list, insert);
			}
			else{
				cout << insert << endl;
				insert_sort(list, insert);
			}
		}
		//delete input
		else if(cmd == "d"){
			int del;
			infile1 >> del;
			delete_val(list, del);
		}
		//number of even inputs
		else if(cmd == "e"){
			int total = 0;
			num_even(list, total);
			outfile << "Number of even elements in the list: " << total << endl;
		}

	}

	outfile.close();//close the files
	infile1.close();

	return 0;

}

void insert_int(intlist*& l,int value){

	intlist* tmp = new intlist;//creates new pointer
	tmp->val = value;//sets value to pointer
	tmp->next = l;//points to previous value
	l = tmp;//sets l to tmp
}

void print_list(intlist* l){
	while(l != NULL){
		cout << l->val << endl;
		l = l->next; //iterates through pointers and outputs values
	}
}

void rev_list(intlist*& l){
	intlist* rev = NULL;//creates new list
	intlist* current = l;
	intlist* next;
		while(current != NULL){
			next  = current->next;
	        current->next = rev;
	        rev = current;
	        current = next;
		}
	l = rev;
}

void delete_val(intlist*& l, int value){

	if(l == NULL){
		return;
	}
	else{
		bool found = false;
		intlist* tmpnext = l;
		//if value to be deleted is the first in the list start on the second node and deallocate the memory
		if(l->val == value){
			l = l->next;
			delete tmpnext;
			found = true;
		}
		//check the list
		else{
			intlist* tmppre = l; //represents previous value
			tmpnext = l->next; //becomes the next value
			while(tmpnext != NULL && found == false){
				if((tmpnext->val == value) && (found == false)){
					found = true; //stops any other values from being changed
					tmppre->next = tmpnext->next; //switch the pointer
					delete(tmpnext); //deallocate memory
				}
				else{
					tmppre = tmppre->next; //move to the next values
					tmpnext = tmpnext->next;
				}
			}
		}
	}
}

void num_even(intlist* l, int& tot){
	intlist* check = l;
	while(check != NULL){
		if(check->val %2 == 0){
			tot++;
		}
		check = check->next;
	}
}

void bubble_sort(intlist*& l, bool& nochange){
	nochange = false;
	if(l == NULL){
		nochange = true;
	}
	else if(l->next != NULL && l != NULL){
		while(!nochange){
			int x = 0;
			nochange = true;
			intlist* tmpnext = l->next;
			if(l->val > tmpnext->val){
				l->next = tmpnext->next;
				tmpnext->next = l;
				l = tmpnext;
				nochange = false;
			}
			intlist* tmppre = l;
			intlist* original = l->next;
			tmpnext = original->next;
			while(tmpnext != NULL){
				if(original->val > tmpnext->val){
					nochange = false;
					if(x == 0){
							original->next = tmpnext->next;
							tmpnext->next = original;
							l->next = tmpnext;
					}
					else{
							original->next = tmpnext->next;
							tmpnext->next = original;
							tmppre->next = tmpnext;
					}
					tmppre = tmpnext;
					tmpnext = original->next;
				}
				else{
					tmppre = original;
					original = original->next;
					tmpnext = original->next;
				}
				x++;
			}
		}
	}
}

void insert_end(intlist*& l, int value){

	bool insert = false;

	if(l == NULL){
		insert_int(l, value);
	}
	else if(l->next == NULL){
		intlist* tmp = new intlist;
		tmp->val = value;
		l->next = tmp;
		tmp->next = NULL;
		insert = true;
	}
	else{
		intlist* tmpnext = l->next;
		while(tmpnext != NULL && insert == false){
			if(tmpnext->next == NULL){
				intlist* tmp = new intlist;
				tmp->val = value;
				tmpnext->next = tmp;
				tmp->next = NULL;
				insert = true;
			}
			tmpnext = tmpnext->next;
		}
	}
}

void insert_sort(intlist*& l, int value){
	bool insert = false;
	if(l->next == NULL){
		intlist* tmp = new intlist;
		tmp->val = value;
		l->next = tmp;
		tmp->next = NULL;
		insert = true;
	}
	else if(l-> val >= value || l == NULL){
		insert_int(l, value);
		insert = true;
	}
	else{
		intlist* tmpins = l;
		intlist* tmpnext = l->next;
		while(tmpnext != NULL && insert == false){
			if(tmpnext->val <= value && tmpnext->next == NULL){
				intlist* tmp = new intlist;
				tmp->val = value;
				tmpnext->next = tmp;
				tmp->next = NULL;
				insert = true;
			}
			else if(value >= tmpins->val && value < tmpnext->val && insert == false){
				insert = true;
				intlist* tmp = new intlist;
				tmp->val = value;
				tmp->next = tmpnext;
				tmpins->next = tmp;
			}
			tmpins = tmpins->next;
			tmpnext = tmpnext->next;
		}
	}

}
