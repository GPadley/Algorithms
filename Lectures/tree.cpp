#include <iostream>
#include <string>

using namespace std;

struct Tree{
    string name;
    Tree* left;
    Tree* right;
};

typedef Tree* treeptr;

string nodeName(treeptr tree);
treeptr rightChild(treeptr tree);
treeptr leftChild(treeptr tree);
void printNames(treeptr tree);
void printNamesBackwards(treeptr tree);
void insertName(string newName, treeptr& tree);
void deleteName(string delName, treeptr& tree);
void deleteRoot(treeptr& tree);
void deleteLeftmost(treeptr& tree, string& leftmost);

int main(){
    cout << "How many people are you going to add to the list?" << endl;
    treeptr list = NULL;
    int count;
    string person;
    cin >> count;
    for(int i = 0; i < count; i++){
        cout << "Enter person " << i+1 << endl;
        cin >> person;
        insertName(person, list );
    }
    cout << "List forwards" << endl;
    printNames(list);
    cout << "Who would you like to delete?" << endl;
    cin >> person;
    deleteName(person, list);
    cout << endl;
    printNames(list);
    return 0;
}

string nodeName(treeptr tree){
    return tree->name;
}

treeptr rightChild(treeptr tree){
    return tree->right;
}

treeptr leftChild(treeptr tree){
    return tree->left;
}

void printNames(treeptr tree){
    if(tree != NULL){
        printNames(leftChild(tree));
        cout << nodeName(tree) << endl;
        printNames(rightChild(tree));
    }
}

void printNamesBackwards(treeptr tree){
    if(tree != NULL){
        printNamesBackwards(rightChild(tree));
        cout << nodeName(tree) << endl;
        printNamesBackwards(leftChild(tree));
    }
}

void insertName(string newName, treeptr& tree){
    treeptr newNode;
    if(tree == NULL){
        newNode = new Tree;
        newNode->name = newName;
        newNode->left = NULL;
        newNode->right = NULL;
        tree = newNode;
    }
    else if(newName < tree->name){
        insertName(newName, tree->left);
    }
    else{
        insertName(newName, tree->right);
    }
}

void deleteName(string delName, treeptr& tree){
    if(tree != NULL){
        if(delName == tree->name){
            deleteRoot(tree);
        }
        else if(delName < tree->name){
            deleteName(delName, tree->left);
        }
        else{
            deleteName(delName, tree->right);
        }
    }

}

void deleteRoot(treeptr& tree){
    treeptr tempnode;
    string leftmost;
    if(tree->right == NULL){
        tempnode = tree;
        tree = tree->left;
        delete(tempnode);
    }
    else{
        deleteLeftmost(tree->right, leftmost);
        tree->name = leftmost;
    }
}

void deleteLeftmost(treeptr& tree, string& leftmost){
    if(tree->left == NULL){
        leftmost = tree->name;
        deleteRoot(tree);
    }
    else{
        deleteLeftmost(tree->left, leftmost);
    }
}
