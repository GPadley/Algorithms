#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


using namespace std;

struct	CP{
	int	id;
	int	data;
	CP	*left;
	CP	*right;
};

typedef CP* CPptr;

void printTree(CPptr tree);
void insertTree(int newid, int newdata, CPptr& tree);
int numLeaves(int& amount, CPptr tree);
void dataReplace(int amount,int change, CPptr tree);
int collatz(int amount);

int main(){

	CPptr tree = NULL;
	int amount, datain;

	cout << "Enter the number of elements" << endl;
	cin >> amount;

	for(int i = 0; i < amount; i++){
		cout << "Enter element " << i+1 << endl;
		cin >> datain;
		insertTree(i+1, datain, tree);
	}

	printTree(tree);

	amount = 0;

	numLeaves(amount, tree);

	cout << "Number of leaves is " <<  amount << endl;

	cout << "Enter which data you would like to change and what value you would like to change it to?" << endl;
	cin >> amount >> datain;

	dataReplace(amount, datain, tree);

	printTree(tree);

	cout << "enter value for Collatz:" << endl;

	cin >> datain;

	amount = collatz(datain);

	cout << "Num steps are: " << amount << endl;

	return 0;
}

void insertTree(int newid, int newdata, CPptr& tree){
    CPptr newNode;
    if(tree == NULL){
        newNode = new CP;
        newNode->id = newid;
        newNode->data = newdata;
        newNode->left = NULL;
        newNode->right = NULL;
        tree = newNode;
    }
    else if(newdata < tree->data){
        insertTree(newid, newdata, tree->left);
    }
    else{
        insertTree(newid, newdata, tree->right);
    }
}

void printTree(CPptr tree){
    if(tree != NULL){
        printTree(tree->left);
        cout << tree->id << " " << tree->data << endl;
        printTree(tree->right);
    }
}

int numLeaves(int& amount,CPptr tree){
	if(tree != NULL){
		if(tree->left == NULL && tree->right == NULL){
			return amount++;
		}
		else{
			numLeaves(amount, tree->left);
			numLeaves(amount, tree->right);
		}
	}
	return amount;
}

void dataReplace(int amount,int change, CPptr tree){
	if(tree != NULL){
		if(tree->data == amount){
			tree->data = change;
			dataReplace(amount, change, tree->right);
		}
		else{
			dataReplace(amount, change, tree->right);
			dataReplace(amount, change, tree->left);
		}
	}
}

int collatz(int amount){
	if(amount == 1){
		return 0;
	}
	else if(amount%2 == 0){
		return 1+collatz(amount/2);
	}
	else{
		return 1+collatz(3*amount+1);
	}
}
