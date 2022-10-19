#pragma once
#include <iostream>

using namespace std;

class Database_BST_Node {
public:
	int bstNum;
	string fileName;
	string imageName;
	Database_BST_Node* left;
	Database_BST_Node* right;
public:
	Database_BST_Node();
};

inline Database_BST_Node::Database_BST_Node() {
	bstNum = 0;
	left = NULL;
	right = NULL;
}

class Database_BST {
public:
	int bstSize;
	Database_BST_Node* root;
public:
	Database_BST();
	~Database_BST();
	void Insert(int fileNum, string filePath, string fileName);
	void Delete();

};

inline Database_BST::Database_BST() {
	bstSize = 0;
	root = NULL;
}

inline Database_BST::~Database_BST() {

}

inline void Database_BST::Insert(int fileNum, string filePath, string fileName)
{
	//if bst size > 300, remove bst node (low number)
	while (bstSize > 300) {
		Delete();
	}

	Database_BST_Node* insert = new Database_BST_Node();
	insert->bstNum = fileNum;
	insert->fileName = filePath;
	insert->imageName = fileName;

	//move bst node(low number)
	Database_BST_Node* p = root, * pp = NULL;
	while (p) {
		pp = p;
		if (insert->bstNum < p->bstNum)
			p = p->left;
		else if (insert->bstNum > p->bstNum)
			p = p->right;
		else if (insert->bstNum = p->bstNum) {
			p = insert;
			break;
		}
	}
	//insert node
	p = insert;
	if (root != NULL) {
		if (insert->bstNum < pp->bstNum)
			pp->left = p;
		else
			pp->right = p;
	}
	else
		root = p;

	bstSize++;
}

inline void Database_BST::Delete()
{
	Database_BST_Node* curNode = root;
	Database_BST_Node* preNode = new Database_BST_Node();
	while (curNode->left != NULL) {
		if (curNode->bstNum > curNode->left->bstNum) {
			preNode = curNode;
			curNode = curNode->left;
		}
	}

	//not exist two child node
	if (curNode->left == NULL && curNode->right == NULL) {
		delete curNode;
		preNode->left = NULL;
		bstSize--;
	}
	//not exist one child node
	else if (curNode->right == NULL) {
		preNode->left = curNode->left;
		delete curNode;
		bstSize--;
	}
	//not exist one child node
	else if (curNode->left == NULL) {
		preNode->left = curNode->right;
		delete curNode;
		bstSize--;
	}
	//exist two child node
	else {
		Database_BST_Node* tempCurNode = curNode->left;
		Database_BST_Node* tempPreNode = new Database_BST_Node();
		while (tempCurNode->right != NULL) {
			tempPreNode = tempCurNode;
			tempCurNode = tempCurNode->right;
		}
		preNode->left = tempCurNode;
		tempCurNode->left = curNode->left;
		tempCurNode->right = curNode->right;
		
		tempPreNode->right = NULL;
		delete(curNode);
		bstSize--;
	}
}
