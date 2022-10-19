#include "Manager.h"

using namespace std;

int main(int argc, char *argv[]) {
	//read command.txt
	ifstream file("command.txt");

	if (file.is_open()) {
		Manager manager = Manager();
		string input;
		vector<string> command;
		FILE* search_image = NULL;
		string image_name;

		int curPosition = 0;
		int position = 0;
		int separator1 = 0;
		int separator2 = 0;

		while (!file.eof()) {
			position = 0;
			curPosition = 0;

			//read command.txt one line
			getline(file, input);

			//prevent reading '\n' once more from the end of the file in ubuntu
			if (!strcmp(input.c_str(), ""))
				continue;

			//Extract first command 
			position = input.find(' ', 0);
			command.push_back(input.substr(0, position)); 
			curPosition = position + 1;

			try {
				if (command[0] == "LOAD") {
					//run LOAD()
					manager.LOAD();
				}
				else if (command[0] == "ADD") {
					if (input == "ADD") {
						throw 200;
					}
					//split ' ' in input
					//Extract commands
					while ((position = input.find(' ', curPosition)) != string::npos) {
						int len = position - curPosition;
						command.push_back(input.substr(curPosition, len));
						curPosition = position + 1;
					}
					command.push_back(input.substr(curPosition));

					//If the number of parameters is insufficient
					if ((command.size()<3)) {
						throw 200;
					}

					//run ADD()
					manager.ADD(command[1], command[2]);
				}
				else if (command[0] == "MODIFY") {

					//Etract second command
					position = input.find(' ', curPosition);
					int len1 = position - curPosition;
					command.push_back(input.substr(curPosition, len1));
					curPosition = position + 1;

					//Etract third command
					separator1 = input.find('\"', curPosition);
					separator2 = input.find('\"', separator1 + 1);
					int len2 = separator2 - separator1;
					command.push_back(input.substr(separator1 + 1, len2 - 1)); // remove ""
					curPosition = separator2 + 2;

					//Etract second command
					command.push_back(input.substr(curPosition));

					//If the number of parameters is insufficient
					if ((command.size() < 4)) {
						throw 300;
					}

					//run MODIFY()
					manager.MODIFY(command[1], command[2], command[3]);
				}
				else if (command[0] == "MOVE") {
					//run MOVE()
					manager.MOVE();
				}
				else if (command[0] == "PRINT") {
					//run PRINT()
					manager.PRINT();
				}
				else if (command[0] == "SEARCH") {

					if (input == "SEARCH") {
						throw 600;
					}

					vector<string> word;

					int separatorFlag = 0;
					int separator[2] = { 0 };
					int i = 0;

					//split '\' in input
					//Extract commands
					while ((position = input.find('\"', curPosition)) != string::npos) {
						separator[i++] = position;
						curPosition = position + 1;
						separatorFlag++;

						if (separatorFlag == 2) {
							int len = separator[1] - separator[0];
							word.push_back(input.substr(separator[0] + 1, len - 1));
							curPosition = separator[1] + 2;
							separatorFlag = 0;
							i = 0;
						}
					}
					//If the number of parameters is insufficient
					if ((word.size() == 0)) {
						throw 600;
					}
					//run SEARCH()
					manager.SEARCH(word);
				}
				else if (command[0] == "SELECT") {

					if (input == "SELECT") {
						throw 700;
					}

					//Etract second command
					position = input.find(' ', curPosition);
					int len1 = position - curPosition;
					command.push_back(input.substr(curPosition, len1));
					curPosition = position + 1;

					//If the number of parameters is insufficient
					if ((command.size() < 2)) {
						throw 700;
					}

					//run SELECT()
					Database_BST_Node* searchNode = manager.SELECT(command[1]);

					//if not exist search searchNode
					if (searchNode == NULL) {
						throw 700;
					}
					else {
						//open search image file
						string image_path = searchNode->fileName + "/" + searchNode->imageName + ".RAW";
						image_name = searchNode->imageName;
						search_image = fopen(image_path.c_str(), "rb");
					}

					//if not exist search image file
					if (search_image == NULL) {
						throw 700;
					}
				}
				else if (command[0] == "EDIT") {

					if (input == "EDIT") {
						throw 800;
					}

					//split ' ' in input
					//Extract commands
					vector<string> parm;
					while ((position = input.find(' ', curPosition)) != string::npos) {
						int len = position - curPosition;
						parm.push_back(input.substr(curPosition, len));
						curPosition = position + 1;
					}
					parm.push_back(input.substr(curPosition));

					//If the number of parameters is insufficient
					if ((parm.size() == 0)) {
						throw 800;
					}

					//if not exist search image file
					if (search_image == NULL) {
						throw 800;
					}
					else {
						//run EDIT()
						manager.EDIT(parm, search_image, image_name);
					}
				}
				else if (command[0] == "EXIT") {
					//run EXIT()
					manager.EXIT();
					//to turn off the memory
					if (search_image != NULL) {
						fclose(search_image);
					}
					return 0;
				}
				else {
					//If not exist command
					throw 777;
				}
			}
			catch(int err_code){
				string filePath = "log.txt";
				ofstream log_file;
				log_file.open(filePath, ios::app);
				if (log_file.is_open()) {
					log_file << "========ERROR========\n";
					log_file << err_code << "\n";
					log_file << "=====================\n";
					log_file.close();
				}
				cout << "========ERROR========" << endl;
				cout << err_code << endl;
				cout << "=====================" << endl;
			}
			
			//reset command
			command.clear();
		}
	}
	return 0;
}