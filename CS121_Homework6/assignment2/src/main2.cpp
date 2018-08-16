#include<iostream>
#include<fstream>
#include<unordered_set>
#include<string>
#include<vector>
#include<algorithm>

// NOTE(clark): I'm just assuming that the strings are the same length. 

#pragma warning( disable : 4710 ) 

using namespace std;

int main() {
	
	unordered_set<string> word_dict;
	string temp;

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

	// Main loop
	char input;
	string filename;
	for(;;) {
		cout << "Please input a lower-case character (Or Q to eqit): ";
		cin >> input;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if(input == 'Q') {
			break;
		}

		if(input < 'a' || input > 'z') {
			cout << "Character was not a-z!" << endl << endl;
			continue;
		}

		filename = "4_letter_words_that_start_with_";
		filename.push_back(input);
		filename += ".txt";

		ofstream outfile(filename);
		if(outfile.is_open()) {
			int count = 0;
			for(const string &str : word_dict) {
				if(count >= 20) {
					outfile << endl;
					count = 0;
				}
				if(str[0] == input) {
					outfile << str << " ";
					count++;
				}
			}
			outfile.close();
		}
		else {
			cout << "Could not open the output file" << endl;
		}
	}
}