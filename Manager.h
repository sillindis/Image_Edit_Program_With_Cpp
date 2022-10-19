#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>

#include <stdio.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Loaded_LIST_FILE.h"
#include "Loaded_LIST.h"
#include "Database_BST.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

class Manager {
public:
	FileList* fileList;
	Loaded_LIST* list;
	Database_BST* bst;
	Queue<Database_BST_Node*>* queue;
	int listSize;

public:
	Manager();
	~Manager();

	void LOAD();
	void ADD(string strFilePath, string strFileName);
	void MODIFY(string strFilePath, string imageName, string imageNum);
	void MOVE();
	void PRINT();
	void SEARCH(vector<string> word);
	Database_BST_Node* SELECT(string fileNum);
	void EDIT(vector<string> parm, FILE* search_image, string image_name);
	void EXIT();

public:
	//void TempPrintList();

private:
	void Remove();
	void Inorder(Database_BST_Node* treeNode, ofstream* file);
	void InorderPrint(Database_BST_Node* treeNode, ofstream* file);
	Database_BST_Node* Preorder(Database_BST_Node* rootNode, string searchNum);
	void BoyerMooreAlgorithm(Database_BST_Node* current_node, string fileName,string searchChar, ofstream* file);
};