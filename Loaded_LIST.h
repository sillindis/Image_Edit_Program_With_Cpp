#pragma once
#include<iostream>

#include "Loaded_LIST_FILE.h"

using namespace std;

class Loaded_LIST_Node {
public:
	string	fileNum;
	string	filePath;
	string	fileName;
	Loaded_LIST_Node* nextNode;
	Loaded_LIST_Node* preNode;

public:
	Loaded_LIST_Node();
};
inline Loaded_LIST_Node::Loaded_LIST_Node() {
	fileNum = "0";
	filePath = "0";
	fileName = "0";
	nextNode = NULL;
	preNode = NULL;
}

class Loaded_LIST {
public:
	Loaded_LIST_Node* mHead;

public:
	Loaded_LIST();
	~Loaded_LIST();
	void InsertNode(FileNode* fileNode, string filNum, string filePath, string fileName);
	void LoadPrintList();
};

inline Loaded_LIST::Loaded_LIST()
{
	mHead = NULL;
}

inline Loaded_LIST::~Loaded_LIST()
{
}

inline void Loaded_LIST::InsertNode(FileNode* fileNode, string fileNum, string filePath, string fileName)
{
	Loaded_LIST_Node* insert = new Loaded_LIST_Node;
	insert->fileNum = fileNum;
	insert->filePath = filePath;
	insert->fileName = fileName;

	//not exist linked list
	if (fileNode->nextLLNode==NULL) {
		fileNode->nextLLNode = insert;
		mHead = fileNode->nextLLNode;
	}
	else {
		Loaded_LIST_Node* temp = mHead;
		while (temp->nextNode != NULL)
			temp = temp->nextNode;
		temp->nextNode = insert;
		insert->preNode = temp;
	}
	
	return;
}

inline void Loaded_LIST::LoadPrintList()
{
	Loaded_LIST_Node* temp = new Loaded_LIST_Node;
	
	cout << "=======LOAD========" << endl;

	temp = mHead;
	while (temp !=NULL)
	{
		cout << temp->fileName << "/" << temp->fileNum << endl;
		temp = temp->nextNode;
	}
	cout << "===================" << endl;

	return;
}
