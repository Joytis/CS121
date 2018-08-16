#include<iostream>
#include<fstream>
#include<unordered_set>
#include<string>
#include<vector>
#include<algorithm>

// NOTE(clark): I'm just assuming that the strings are the same length. 

#pragma warning( disable : 4710 ) 
#define STRING_LENGTH (10)

using namespace std;

int main(int argc, char **argv) {
	
	unordered_set<string> word_dict;
	string temp;
	vector<string> row_lines;
	std::vector<string> column_lines;

	if(argc != 2) {
		cout << "Please give a file name to open" << endl;
		exit(0);
	}


	// Read the dictionary.
	ifstream infile("dictionary_of_four_letter_words.txt");
	if(!infile.good()) {
		cout << "File missing or corrupt or in use or something" << endl;
		return 0;
	}

	while(infile.good()) {
		infile >> temp;
		// Insert into the unordered set. 
		if(word_dict.find(temp) == word_dict.end()) {
			word_dict.insert(temp);
		}
	}
	infile.close();

	// Get input dawg
	ifstream input(argv[1]);
	if(!input.good()) {
		cout << "Input file missing or corrupt or in use or something." << endl;
		return 0;
	}
	while(input.good()) {
		input >> temp;
		row_lines.push_back(temp);

	}
	input.close();

	// Store 'column' strings. 
	// This is inefficient, but whatever. 
	for(unsigned int i = 0; i < STRING_LENGTH; i ++) {
		temp.clear();
		for(const string &str : row_lines) {
			temp.push_back(str[i]);
		}
		column_lines.push_back(temp);
	}

	cout << "Words found in rows: " << endl;
	string sub;
	for(const string str : row_lines) {
		// Check all the rows
		for(unsigned int i = 0; i <= STRING_LENGTH - 4; i++) {
			sub = str.substr(i, 4);
			if(word_dict.find(sub) != word_dict.end()) {
				cout << sub << ", ";
			}
			reverse(sub.begin(), sub.end());
			if(word_dict.find(sub) != word_dict.end()) {
				cout << sub << ", ";
			}
		}
	}

	cout << endl << endl << "Words found in columns: " << endl;
	for(const string str : column_lines) {
		// Check all the rows
		for(unsigned int i = 0; i <= STRING_LENGTH - 4; i++) {
			sub = str.substr(i, 4);
			if(word_dict.find(sub) != word_dict.end()) {
				cout << sub << ", ";
			}
			reverse(sub.begin(), sub.end());
			if(word_dict.find(sub) != word_dict.end()) {
				cout << sub << ", ";
			}

		}
	}
	cout << endl;

	return 0;
}

