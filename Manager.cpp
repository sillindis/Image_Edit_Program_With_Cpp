#pragma warning(disable:4996)

#include "Manager.h"

Manager::Manager()
{
	listSize = 0;
	fileList = new FileList();
	list = new Loaded_LIST();
	bst = new Database_BST();
	queue = new Queue<Database_BST_Node*>(300);
}

Manager::~Manager()
{
	free(fileList);
	free(list);
	free(bst);
	free(queue);
}

void Manager::LOAD()
{
	//open filesnumbers.csv
	FILE* file = NULL;
	file = fopen("img_files/filesnumbers.csv", "rb");

	if (file != NULL) {
		char str_tmp[1024];

		//insert 'img_files' folder at file list
		fileList->InsertNode("img_files");
		FileNode* fileNode = fileList->fHead;

		//pass BOM in .csv
		fseek(file, 3, SEEK_SET);

		while (!feof(file)) {
			//prevent reading '\n' once more from the end of the file
			if (fgets(str_tmp, 1024, file) == NULL) break;
			string line(str_tmp);

			stringstream ssTemp(line);
			string sTemp;
			vector<string> vectorTemp;

			//split ',' in csv
			while (getline(ssTemp, sTemp, ',')) { //ex) split 100, filename
				vectorTemp.push_back(sTemp);
			}

			string fullname = vectorTemp[1]; 
			size_t lastindex = fullname.find_last_of("."); //remove .RAW
			string fileName = fullname.substr(0, lastindex);

			//insert Loaded linked list
			list->InsertNode(fileNode, vectorTemp[0], "img_files", fileName);
			listSize++;
		}
		list->LoadPrintList();
		fclose(file);

		//to print the result in log.txt
		string filePath = "log.txt";
		ofstream log_file;
		log_file.open(filePath, ios::out);
		if (log_file.is_open()) {
			Loaded_LIST_Node* temp = new Loaded_LIST_Node;
			temp = list->mHead;
			log_file << "=======LOAD========\n";
			while (temp != NULL)
			{
				log_file << temp->fileName << "/" << temp->fileNum << "\n";
				temp = temp->nextNode;
			}
			log_file << "===================\n";
			log_file.close();
		}
	}
	else {
		//If not exist csv file
		throw 100;
	}
}

void Manager::ADD(string strFilePath, string strFileName)
{
	//open new folder
	string path = strFilePath + "/" + strFileName;
	FILE* file = NULL;
	file = fopen(path.c_str(), "rb");

	if (file != NULL) {
		char str_tmp[1024];

		//insert new folder at file list
		fileList->InsertNode(strFilePath);
		FileNode* fileNode = fileList->fHead;
		while (fileNode->nextFNode != NULL) {
			fileNode = fileNode->nextFNode;
		}

		//pass BOM
		fseek(file, 3, SEEK_SET);

		while (!feof(file)) {
			//prevent reading '\n' once more from the end of the file
			if (fgets(str_tmp, 1024, file) == NULL) break;
			string line(str_tmp);

			stringstream ssTemp(line);
			string sTemp;
			vector<string> vectorTemp;

			//split ',' in csv
			while (getline(ssTemp, sTemp, ',')) { //ex) split 100, filename
				vectorTemp.push_back(sTemp);
			}

			string fullname = vectorTemp[1];
			size_t lastindex = fullname.find_last_of("."); //remove .RAW
			string fileName = fullname.substr(0, lastindex);

			//insert Loaded linked list
			list->InsertNode(fileNode, vectorTemp[0], "new_files", fileName);
			listSize++;

			//IF a new node comes in and the total number of nodes exceeds 300,
			//remove first node in linked list
			while (listSize > 100) {
				Remove();
			}
		}

		//to print the result in log.txt
		string filePath = "log.txt";
		ofstream log_file;
		log_file.open(filePath, ios::app);
		if (log_file.is_open()) {
			log_file << "========ADD========\n";
			log_file << "SUCCESS\n";
			log_file << "===================\n";
			log_file.close();
		}
		cout << "========ADD========" << endl;
		cout << "SUCCESS" << endl;
		cout << "===================" << endl;
	}
	else {
		//If not exist csv file
		throw 200;
	}
}

void Manager::MODIFY(string strFilePath, string imageName, string imageNum)
{
	//to save the information of the node to be modified
	Loaded_LIST_Node* modify = new Loaded_LIST_Node();
	modify->filePath = strFilePath;
	modify->fileName = imageName;
	modify->fileNum = imageNum;

	FileNode* curFNode = fileList->fHead;

	bool modifyFlag = false;
	
	//find modify node in file list
	while (curFNode != NULL) {
		//find modify node in file list
		if (curFNode->fileName == strFilePath) {
			//find modify node in Loaded linked list
			if (curFNode->nextLLNode->fileName == imageName) { //head node
				//If the num of the node to be modified is the same as the existing num
				if (curFNode->nextLLNode->fileNum == imageNum) {
					throw 300;
				}
				//remove original node, add modify node
				Loaded_LIST_Node* remove = curFNode->nextLLNode;
				curFNode->nextLLNode = modify;
				modify->nextNode = remove->nextNode;
				delete(remove);

				//to print the result in log.txt
				string filePath = "log.txt";
				ofstream log_file;
				log_file.open(filePath, ios::app);
				if (log_file.is_open()) {
					log_file << "========MODIFY========\n";
					log_file << "SUCCESS\n";
					log_file << "======================\n";
					log_file.close();
				}
				cout << "========MODIFY========" << endl;
				cout << "SUCCESS" << endl;
				cout << "=====================" << endl;
				modifyFlag = true;
				return;
			}
			Loaded_LIST_Node* curLNode = curFNode->nextLLNode;
			while (curLNode->nextNode != NULL) {
				//find modify node in Loaded linked list
				if (curLNode->nextNode->fileName == imageName) {
					//If the num of the node to be modified is the same as the existing num
					if (curLNode->nextNode->fileNum == imageNum) {
						throw 300;
					}
					//remove original node, add modify node
					Loaded_LIST_Node* remove = curLNode->nextNode;
					curLNode->nextNode = modify;
					modify->nextNode = remove->nextNode;
					remove->nextNode->preNode = modify;
					modify->preNode = curLNode;
					delete(remove);

					//to print the result in log.txt
					string filePath = "log.txt";
					ofstream log_file;
					log_file.open(filePath, ios::app);
					if (log_file.is_open()) {
						log_file << "========MODIFY========\n";
						log_file << "SUCCESS\n";
						log_file << "======================\n";
						log_file.close();
					}

					cout << "========MODIFY========" << endl;
					cout << "SUCCESS" << endl;
					cout << "=====================" << endl;

					modifyFlag = true;
					return;
				}
				curLNode = curLNode->nextNode;
			}
		}
		curFNode = curFNode->nextFNode;
	}
	if (modifyFlag == false) {
		//not exist modify node in liked list
		throw 300;
	}
}

void Manager::MOVE()
{
	//not exist loaded linked list
	if (listSize == 0) {
		throw 400;
	}

	FileNode* curFileNode = fileList->fHead;
	while (curFileNode->nextFNode != NULL) {
		curFileNode = curFileNode->nextFNode;
	}

	while(curFileNode != NULL){
		Loaded_LIST_Node* curLLNode = curFileNode->nextLLNode;
		while (curLLNode->nextNode != NULL) {
			curLLNode = curLLNode->nextNode;
		}

		Loaded_LIST_Node* LNode_temp = curLLNode->preNode;
		while (LNode_temp != NULL) {
			////move linked list to bst
			bst->Insert(stoi(curLLNode->fileNum), curLLNode->filePath, curLLNode->fileName);
			delete curLLNode;
			listSize--;
			curLLNode = LNode_temp;
			LNode_temp = curLLNode->preNode;
		}
		//last node move linked list to bst 
		bst->Insert(stoi(curLLNode->fileNum), curLLNode->filePath, curLLNode->fileName);

		FileNode* FNode_temp = curFileNode->preFNode;
		delete curFileNode;
		curFileNode = FNode_temp;
	}

	//to print the result in log.txt
	string filePath = "log.txt";
	ofstream log_file;
	log_file.open(filePath, ios::app);
	if (log_file.is_open()) {
		log_file << "========MOVE==========\n";
		log_file << "SUCCESS\n";
		log_file << "======================\n";
		log_file.close();
	}

	cout << "========MOVE========" << endl;
	cout << "SUCCESS" << endl;
	cout << "=====================" << endl;
}

void Manager::PRINT() 
{
	//not exist bst
	if (bst->root == NULL) {
		throw 500;
	}

	//to print the result in log.txt
	string filePath = "log.txt";
	ofstream log_file;
	log_file.open(filePath, ios::app);
	if (log_file.is_open()) {
		Database_BST_Node* treeNode = bst->root;
		log_file << "========PRINT=============\n";
		cout << "======PRINT================" << endl;
		Inorder(treeNode, &log_file);
		cout << "===========================" << endl;
		log_file << "===========================\n";
		log_file.close();
	}
}

void Manager::SEARCH(vector<string> word)
{
	//not exist bst
	if (bst->root == NULL) {
		throw 600;
	}
	
	//postorder Interative
	Stack<Database_BST_Node*>* stack1 = new Stack<Database_BST_Node*>(300);
	Stack<Database_BST_Node*>* stack2 = new Stack<Database_BST_Node*>(300);

	// push root to first stack
	stack1->Push(bst->root);

	Database_BST_Node* current_node;

	while (!stack1->IsEmpty()) {
		// Pop an item from stack1 and push it to stack2
		current_node = stack1->Pop();
		stack2->Push(current_node);
		
		// Push left and right children
		if (current_node->left)
			stack1->Push(current_node->left);
		if (current_node->right)
			stack1->Push(current_node->right);
	}

	//insert bst->queue
	while (!stack2->IsEmpty()) {
		current_node = stack2->Pop();
		//cout << "current_node: " << current_node->bstNum << endl;;
		queue->Enqueue(current_node);
	}

	// BoyerMooreAlgorithm Search
	//to print the result in log.txt
	string filePath = "log.txt";
	ofstream file;
	file.open(filePath, ios::app);
	if (file.is_open()) {
		Database_BST_Node* queue_currnet_node;
		file << "========SEARCH==========\n";
		cout << "=======SEARCH===============" << endl;
		while (!queue->IsEmpty()) {
			queue_currnet_node = queue->Dequque();
			for (int i = 0; i < word.size(); i++) {
				BoyerMooreAlgorithm(queue_currnet_node, queue_currnet_node->imageName, word[i], &file);
			}
		}
		cout << "============================" << endl;
		file << "======================\n";
		file.close();
	}

	free(stack1);
	free(stack2);
	return;
}

Database_BST_Node* Manager::SELECT(string fileNum)
{
	//not exist bst
	if (bst->root == NULL) {
		throw 700;
	}

	//reculsive preorder
	Database_BST_Node* searchNode = Preorder(bst->root, fileNum);
	
	//if find search node
	if (searchNode != nullptr) {
		//to print the result in log.txt
		string filePath = "log.txt";
		ofstream log_file;
		log_file.open(filePath, ios::app);
		if (log_file.is_open()) {
			log_file << "========SELECT==========\n";
			log_file << "SUCCESS\n";
			log_file << "========================\n";
			log_file.close();
		}
		cout << "==========SELECT============" << endl;
		cout << "SUCCESS" << endl;
		cout << "==========================" << endl;

		return searchNode;
	}
	else {
		//not exist file num
		throw 700;
	}
	return NULL;
}

void Manager::EDIT(vector<string> parm, FILE* search_image, string image_name)
{
	//not exist image file
	if (search_image == NULL) {
		throw 800;
	}

	int width = 256;
	int height = 256;
	FILE* output_file = NULL;

	//open RAW file
	unsigned char* input_data = new unsigned char[256 * 256];
	fread(input_data, sizeof(unsigned char), width * height, search_image);

	//make directory 'Result'
	//int dir = mkdir("Result", 0755);
	int dir = mkdir("./Result");

	if (parm[0] == "-f") {
		//create stack
		Stack<unsigned char>* stackRaw = new Stack<unsigned char>(256 * 256);
		unsigned char* output_data = new unsigned char[256 * 256];
		for (int i = 0; i < 256 * 256; i++) {
			stackRaw->Push(input_data[i]);
		}
		for (int i = 0; i < 256 * 256; i++) {
			output_data[i] = stackRaw->Pop();
		}
		//make file (file name)_flipped
		string makeFilePath = "Result/" + image_name + "_flipped.RAW";
		output_file = fopen(makeFilePath.c_str(), "wb");
		fwrite(output_data, sizeof(unsigned char), width * height, output_file);

		free(stackRaw);
	}
	else if (parm[0] == "-l") {
		string parm_string(parm[1]);
		
		//If the parameter is not number
		if (const char* str_tmp = parm_string.c_str()) {
			for (int i = 0; i < strlen(str_tmp); i++) {
				if ((str_tmp[i] < 48) || str_tmp[i] > 57) {
					throw 800;
				}
			}
		}
		else {
			throw 800;
		}

		unsigned char value = stoi(parm[1]);

		Queue<unsigned char>* queueRaw = new Queue<unsigned char>(256*256);
		unsigned char* output_data = new unsigned char[256 * 256];
		for (int i = 0; i < 256 * 256; i++) {
			queueRaw->Enqueue(input_data[i]);
		}
		for (int i = 0; i < 256 * 256; i++) { //brighten up the image
			unsigned char pop_value = queueRaw->Dequque();
			unsigned char result_value = ((int)pop_value + value > 255) ? 255 : pop_value + value;
			output_data[i] = result_value;
		}
		//make file (file name)_adjusted
		string makeFilePath = "Result/" + image_name + "_adjusted.RAW";
		output_file = fopen(makeFilePath.c_str(), "wb");
		fwrite(output_data, sizeof(unsigned char), width * height, output_file);
	}
	else if (parm[0] == "-r") {
		unsigned char* output_data = new unsigned char[256 * 256 / 4];

		//calculate the average value of the four adjacent cells and enter it in one cell
		for (int i = 0; i < 256 * 256 / 4; i++) {
			unsigned char result_value = (input_data[4 * i] + input_data[4 * i + 1] + input_data[4 * i + 2] + input_data[4 * i + 3])/4;
			output_data[i] = result_value;
		}
		//make file (file name)_resized
		string makeFilePath = "Result/" + image_name + "_resized.RAW";
		output_file = fopen(makeFilePath.c_str(), "wb");
		fwrite(output_data, sizeof(unsigned char), width * height / 4, output_file);
	}
	else {
		//not exist parameter
		throw 800;
	}

	//to print the result in log.txt
	string filePath = "log.txt";
	ofstream log_file;
	log_file.open(filePath, ios::app);
	if (log_file.is_open()) {
		log_file << "========EDIT==========\n";
		log_file << "SUCCESS\n";
		log_file << "========================\n";
		log_file.close();
	}
	cout << "==========EDIT============" << endl;
	cout << "SUCCESS" << endl;
	cout << "==========================" << endl;

	fclose(output_file);
}

void Manager::EXIT()
{
	//to print the result in log.txt
	string filePath = "log.txt";
	ofstream file;
	file.open(filePath, ios::app);
	if (file.is_open()) {
		file << "========EXIT==========\n";
		file << "SUCCESS\n";
		file << "======================\n";
	}
	file.close();
	cout << "=======EXIT===============" << endl;
	cout << "SUCCESS" << endl;
	cout << "============================" << endl;
}

/// <summary>
/// =======================private==========================
/// </summary>

void Manager::Remove()
{
	Loaded_LIST_Node* remove = new Loaded_LIST_Node();
	Loaded_LIST_Node* temp = fileList->fHead->nextLLNode;

	//find liked list first node
	if (fileList->fHead->nextLLNode->nextNode != NULL) {
		fileList->fHead->nextLLNode = fileList->fHead->nextLLNode->nextNode;
	}
	else {
		fileList->fHead = fileList->fHead->nextFNode;
	}
	remove = temp;
	delete remove;
	listSize--;
	return;
}

void Manager::Inorder(Database_BST_Node* treeNode, ofstream* file)
{
	//recursive inoder
	if (treeNode != NULL) {
		Inorder(treeNode->left, file);
		InorderPrint(treeNode, file);
		Inorder(treeNode->right, file);
	}
}

void Manager::InorderPrint(Database_BST_Node* treeNode, ofstream* file)
{ 
	//print inoder and print result log.txt
	cout << treeNode->fileName << "/" << "\"" << treeNode->imageName << "\"" << "/" << treeNode->bstNum << endl;
	*file << treeNode->fileName << "/" << "\"" << treeNode->imageName << "\"" << "/" << treeNode->bstNum << "\n";
}

Database_BST_Node* Manager::Preorder(Database_BST_Node* rootNode, string searchNum)
{
	//if not exist bst root
	if (rootNode == NULL) {
		return nullptr;
	}
	// Create an empty stack and push root to it
	Stack<Database_BST_Node*>* stack1 = new Stack<Database_BST_Node*>(300);
	stack1->Push(rootNode);

	Database_BST_Node* node = new Database_BST_Node();
	while (!stack1->IsEmpty()) {
		// Pop the top item from stack and print it
		node = stack1->Pop();
		if (node->bstNum == stoi(searchNum)) {
			return node;
		}

		if (node->right)
			stack1->Push(node->right);
		if (node->left)
			stack1->Push(node->left);
	}
	free(stack1);
	return nullptr;
}

void Manager::BoyerMooreAlgorithm(Database_BST_Node* current_node, string fileName, string searchChar, ofstream* file)
{
	int searchChar_size = searchChar.size();
	int fileName_size = fileName.size();

	int badchar[256];

	//badCharHeuristic
	int i;
	for (i = 0; i < 256; i++)
		badchar[i] = -1;
	for (i = 0; i < searchChar_size; i++)
		badchar[(int)searchChar[i]] = i;

	int s = 0;

	while (s <= (fileName_size - searchChar_size))
	{
		int j = searchChar_size - 1;

		while (j >= 0 && searchChar[j] == fileName[s + j])
			j--;

		if (j < 0)
		{
			//print search image file
			cout << "\"" << current_node->imageName << " / " << current_node->bstNum << "\"" << endl;
			*file << "\"" << current_node->imageName << " / " << current_node->bstNum << "\"" << "\n";

			s += (s + searchChar_size < fileName_size) ? searchChar_size - badchar[fileName[s + searchChar_size]] : 1;

		}

		else
			s += max(1, j - badchar[fileName[s + j]]);
	}
}

//void Manager::TempPrintList()
//{
//	FileNode* curFileNode = fileList->fHead;
//	Loaded_LIST_Node* curLoadListNode;
//
//	while (curFileNode != NULL) {
//		cout << curFileNode->fileName << "->" << endl;
//		curLoadListNode = curFileNode->nextLLNode;
//		while (curLoadListNode != NULL) {
//			cout << curLoadListNode->fileNum;
//			if (curLoadListNode->nextNode != NULL)
//				cout << ", ";
//			curLoadListNode = curLoadListNode->nextNode;
//		}
//		cout << endl;
//		curFileNode = curFileNode->nextFNode;
//	}
//
//	//cout << "size: " << listSize << endl;
//}