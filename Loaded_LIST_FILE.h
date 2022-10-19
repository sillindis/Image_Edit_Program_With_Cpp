#pragma once
#include <string>
using namespace std;

class Loaded_LIST_Node;

class FileNode {
public:
	FileNode* nextFNode;
	FileNode* preFNode;
	Loaded_LIST_Node* nextLLNode;
	string fileName;
public:
	FileNode();
};

inline FileNode::FileNode() {
	nextFNode = NULL;
	nextLLNode = NULL;
	fileName = "0";
}

class FileList {
public:
	FileNode* fHead;
public:
	FileList();
	void InsertNode(string fileName);
};
inline FileList::FileList() {
	fHead = NULL;
}
inline void FileList::InsertNode(string fileName) {
	FileNode* insert = new FileNode();
	insert->fileName = fileName;

	//if not exist file node linked list
	if (fHead == NULL) {
		fHead = insert;
	}
	else {
		FileNode* temp = fHead;
		while (temp->nextFNode != NULL) {
			temp = temp->nextFNode;
		}
		temp->nextFNode = insert;
		insert->preFNode = temp;
	}

}