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
				insert_end(list, val);
			}

			infile2.close();

		}
		//bubble sort input
		else if(cmd == "s"){
			bubble_sort(list, sorted);
		}
		//write to file input
		else if(cmd == "w"){
			intlist* outlist = list;
			//makes outlist equal to list to be able to output it into the text fill

			while(outlist != NULL){
				outfile << endl << outlist->val;
				outlist = outlist->next;
			}
		}
		//insert into list function
		else if(cmd == "i"){
			int insert;
			infile1 >> insert;
			if(sorted == false){
				//if no sorting has been completed add onto the end of the list
				insert_end(list, insert);
			}
			else{
				//in the case that the list has been sorted the new value is added into the order
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

			outfile << endl << "Number of even elements in the list: " << total << endl;
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
		intlist* tmpnext = l;
		//if value to be deleted is the first in the list start on the second node and deallocate the memory
		if(l->val == value){
			l = l->next;
			delete tmpnext;
			return;
		}
		//check the list
		else{
			intlist* tmppre = l; //represents previous value
			tmpnext = l->next; //becomes the next value
			while(tmpnext != NULL){
				if(tmpnext->val == value){
					tmppre->next = tmpnext->next; //switch the pointer
					delete(tmpnext); //deallocate memory
					return;
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
	//if the list is empty return
	if(l == NULL){
		nochange = true;
		return;
	}
	//traverses the list
	else if(l->next != NULL){
		while(!nochange){
			int x = 0;
			//count to see how many sorts have been done
			nochange = true;
			//states that nothing has been altered
			intlist* tmpnext = l->next;
			//makes tmpnext equal to the next value of the list
			if(l->val > tmpnext->val){
				//if the first value of the list is greater than the second
				l->next = tmpnext->next;
				//first value takes the next pointer
				tmpnext->next = l;
				//point tmpnext at l
				l = tmpnext;
				//make tmpnext the first value of list
				nochange = false;
				//change has been made
			}
			intlist* tmppre = l;
			//linked to the previous value of the list
			intlist* original = l->next;
			//original points to the second value in the list
			tmpnext = original->next;
			//tmpnext points to the third value of the list
			while(tmpnext != NULL){
				if(original->val > tmpnext->val){
					//if the x value is more than the x+1 placed value
					nochange = false;
					if(x == 0){
						//if the second cvalue in the list needs swapping the the pointer l has needs changing
						original->next = tmpnext->next;
						tmpnext->next = original;
						l->next = tmpnext;
					}
					else{
						//swaps all the pointers
						original->next = tmpnext->next;
						tmpnext->next = original;
						tmppre->next = tmpnext;
					}
					//if the pointers have been swapped, original is now in the next place so dont move on
					tmppre = tmpnext;
					tmpnext = original->next;
				}
				else{
					//if nothing is changed, move onto the next item in the list
					tmppre = original;
					original = original->next;
					tmpnext = original->next;
				}
				x++;
			}
		}
	}
	nochange = true;
}

void insert_end(intlist*& l, int value){

	if(l == NULL){
		//if the list is empty, add onto the start of the list
		insert_int(l, value);
		return;
	}
	else if(l->next == NULL){
		//if there is one item, add onto the end
		intlist* tmp = new intlist;
		tmp->val = value;
		l->next = tmp;
		tmp->next = NULL;
		return;
	}
	else{
		//move through the list until you get to the end of the list and add onto the end
		intlist* tmpnext = l->next;
		while(tmpnext != NULL){
			if(tmpnext->next == NULL){
				intlist* tmp = new intlist;
				tmp->val = value;
				tmpnext->next = tmp;
				tmp->next = NULL;
				return;
			}
			tmpnext = tmpnext->next;
		}
	}
}

void insert_sort(intlist*& l, int value){
	//if the list has one item and the value is greater than the list value add onto end
	if(l->next == NULL && l->val < value){
		intlist* tmp = new intlist;
		tmp->val = value;
		l->next = tmp;
		tmp->next = NULL;
		return;
	}
	//of the list is empty or the first item is greater than the value, add to the start of the list
	else if(l-> val >= value || l == NULL){
		insert_int(l, value);
		return;
	}
	//to declare that it has been added to the list
	else{
		intlist* tmpins = l;
		intlist* tmpnext = l->next;
		while(tmpnext != NULL){
			if(tmpnext->val <= value && tmpnext->next == NULL){
				intlist* tmp = new intlist;
				tmp->val = value;
				tmpnext->next = tmp;
				tmp->next = NULL;
				return;
			}
			else if(value >= tmpins->val && value < tmpnext->val){
				intlist* tmp = new intlist;
				tmp->val = value;
				tmp->next = tmpnext;
				tmpins->next = tmp;
				return;
			}
			tmpins = tmpins->next;
			tmpnext = tmpnext->next;
		}
	}

}
