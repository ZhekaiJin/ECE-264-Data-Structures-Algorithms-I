

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <list>

#include "SimpleList.hpp"

using namespace std;
//include the standard namspace;

//delcare three big class storing pointers to different types of stacks and queues;
list<SimpleList<int> *> listSLi;
list<SimpleList<double> *> listSLd;
list<SimpleList<string> *> listSLs;


//use template to realize the search, which run with an iterator, a linear time running time;
template <typename T>
SimpleList<T> * search_list (string name, list<SimpleList<T> *> * l) {
    //call the iterator past the front and the end of the big list;
	typename list<SimpleList<T> *>::const_iterator it = l->begin(),
		end = l->end();
	
    // use a for loop to see if the target list can be found: if found renturn the pointer, otherwise return nullptr;
	for (; it != end; ++it) {
		if ((*it)->listName == name) return *it;
	}

	return nullptr;
}

//function which process the command and ouput it to the file;
void process_file (string input, string output) {
    //use input and output stream to instantiate input and output file;
    ifstream in_file;
    ofstream out_file;
	
    //declare three pointers pointer to different type of linked lists;
	SimpleList<int> * pSLi;
	SimpleList<double> * pSLd;
	SimpleList<string> * pSLs;

    // open the input and output file (clear it while open);
    in_file.open(input.c_str(), ios::in);
    out_file.open(output.c_str(), ios::out | ios::trunc);

    //cheack if the file is opened, otherwise invalid inputfile name
    if (in_file.is_open()) {
        // declare the parsing stage, take the first word to be cmd and secodn word target, and the third word target;
        string cmd, target, value;
        string line_contents;

        //
        while (getline(in_file, line_contents)){
            //use isstringstream to parse the line into strings;
            istringstream iss(line_contents);
            
            // read the first two word of the line;
            iss >> cmd >> target;
            
            // outpute processing command as required;
            out_file << "PROCESSING COMMAND: " << line_contents << endl;

            // if first word is create, then switch it into three cases according to the first word of the second word,i,d,s according to type;
			if (cmd == "create") {
                // read the last value (a stack or a queue);
				iss >> value;
				switch (target.at(0)) {
					case 'i':
                        // do search, if found, invlaid command, if not do push for stack and queue accordingly;
						if (search_list (target, &listSLi) != nullptr) {
							out_file << "ERROR: This name already exists!" << endl;
						} else if (value == "stack") {
							pSLi = new Stack<int>(target);
							listSLi.push_front(pSLi);
						} else {
							pSLi = new Queue<int>(target);
							listSLi.push_front(pSLi);
						}
						break;
					case 'd':
						if (search_list (target, &listSLd) != nullptr) {
							out_file << "ERROR: This name already exists!" << endl;
						} else if (value == "stack") {
							pSLd = new Stack<double>(target);
							listSLd.push_front(pSLd);
						} else {
							pSLd = new Queue<double>(target);
							listSLd.push_front(pSLd);
						}
						break;
					case 's':
						if (search_list (target, &listSLs) != nullptr) {
							out_file << "ERROR: This name already exists!" << endl;
						} else if (value == "stack") {
							pSLs = new Stack<string>(target);
							listSLs.push_front(pSLs);
						} else {
							pSLs = new Queue<string>(target);
							listSLs.push_front(pSLs);
						}
				}
                //if the command is push switch case it into three data type to according with the template search. Then do the search function and same operation as create;
			} else if (cmd == "push") {
				iss >> value;
				switch (target.at(0)) {
					case 'i':
						pSLi = search_list (target, &listSLi);
                        // if found push it properly with the value change into an integer;
						if (pSLi != nullptr) {
							pSLi->push(stoi(value));
						} else {
							out_file << "ERROR: This name does not exist!" << endl;
						}
						break;
					case 'd':
						pSLd = search_list (target, &listSLd);
                        // if found push it properly with the value change into an double;
						if (pSLd != nullptr) {
							pSLd->push(stod(value));
						} else {
							out_file << "ERROR: This name does not exist!" << endl;
						}
						break;
					case 's':
						pSLs = search_list (target, &listSLs);
						if (pSLs != nullptr) {
							pSLs->push(value);
						} else {
							out_file << "ERROR: This name does not exist!" << endl;
						}
						break;
                }
			} else {
                // if it is a pop cheack, do the search like above , but also return value poped to the outputfile and check the size of the list to make sure the command is valid;
				switch (target.at(0)) {
					case 'i':
						pSLi = search_list(target, &listSLi);
						if (pSLi != nullptr) {
							if (pSLi->getSize() != 0) {
								out_file << "Value popped: " << pSLi->pop() << endl;
							} else {
								out_file << "ERROR: This list is empty!" << endl;
							}
						} else {
							out_file << "ERROR: This name does not exist!" << endl;
						}
						break;
					case 'd':
						pSLd = search_list(target, &listSLd);
						if (pSLd != nullptr) {
							if (pSLd->getSize() != 0) {
								out_file << "Value popped: " << pSLd->pop() << endl;
							} else {
								out_file << "ERROR: This list is empty!" << endl;
							}
						} else {
							out_file << "ERROR: This name does not exist!" << endl;
						}
						break;
					case 's':
						pSLs = search_list(target, &listSLs);
						if (pSLs != nullptr) {
							if (pSLs->getSize() != 0) {
								out_file << "Value popped: " << pSLs->pop() << endl;
							} else {
								out_file << "ERROR: This list is empty!" << endl;
							}
						} else {
							out_file << "ERROR: This name does not exist!" << endl;
						}
				}
			}
        }

        in_file.close();  // close both files to ensure it can be reused again;
        out_file.close();
    } else {
		out_file << "ERROR: The input file does not exist!";
	}
}

int main(int argc, char** argv) {
    string input_file, output_file;

    //ask for the input and output name;
    cout << "Enter name of input file: ";
    cin >> input_file;

    cout << "Enter name of output file: ";
    cin >> output_file;

    //use the process function;
	process_file (input_file, output_file);
    
    return 0;
}
