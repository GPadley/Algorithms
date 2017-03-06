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
void numNodes(int& num, CPptr tree);
void numEven(int& num, CPptr tree);
void maxNode(CPptr& maxtree, CPptr tree);
void totData(int& num, CPptr tree);
void idDepth(int id, int& depth, bool& idfound, CPptr tree);

int main(int argc, char* argv[]){
	CPptr tree = NULL;
	CPptr maxnode = NULL;
	int amount, idin, datain;
	ifstream infile1;
	string cmdfile;

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

	while(infile1 >> idin >> datain){
		insertTree(idin, datain, tree);
	}

	amount = 0;

	numNodes(amount, tree);
		if(amount == 0){
			cout << "The list has no nodes" << endl;
		}
		else{
			cout << "The number of nodes is " << amount << endl;
		}

	amount = 0;

	numEven(amount, tree);
		if(amount == 0){
			cout << "The list has no even nodes" << endl;
		}
		else{
			cout << "The number of even nodes is " << amount << endl;
		}

	maxnode = tree;

	maxNode(maxnode, tree);
		if(maxnode == NULL){
			cout << "The tree is empty"  << endl;
		}
		else{
			cout << "The max node is ID: " << maxnode->id << " Data: " << maxnode->data << endl;
		}

	amount = 0;

	totData(amount, tree);
		cout << "The sum of all the data is: " << amount << endl;

	cout << "Enter the id of the depth you would like to know:" << endl;
	cin >> idin;
	amount = -1;
	bool found = false;
	idDepth(idin, amount, found, tree);

	if(found == false){
		cout << "The id doesn't exist in the list" << endl;
	}
	else{
		cout << "The depth is: " << amount << endl;
	}

	printTree(tree);

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

void numEven(int& num, CPptr tree){
    if(tree != NULL){
		numEven(num, tree->left);
		if(tree->data % 2 == 0){
			num++;
		}
        numEven(num, tree->right);
    }
}

void numNodes(int& num, CPptr tree){
    if(tree != NULL){
		numNodes(num, tree->left);
        num++;
        numNodes(num, tree->right);
    }
}

void maxNode(CPptr& maxtree, CPptr tree){
	if(tree != NULL){
		if(tree->right == NULL){
			maxtree = tree;
		}
		else{
			maxNode(maxtree, tree->right);
		}
	}
}

void totData(int& num, CPptr tree){
	if(tree != NULL){
		totData(num, tree->left);
		num = num + tree->data;
		totData(num, tree->right);
	}
}

void idDepth(int id, int& depth, bool& idfound, CPptr tree){
	if(tree != NULL){
		depth++;
		if(id == tree->id){
			idfound = true;
		}
		if(idfound == false){
			idDepth(id, depth, idfound, tree->left);
			if(idfound == false){
				idDepth(id, depth, idfound, tree->right);
				if(idfound == false){
					depth--;
				}
			}
		}
	}
}
