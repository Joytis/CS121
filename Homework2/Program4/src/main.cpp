#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

int main(int argc, char ** argv) {
	
	ifstream in_file("UAH_sample.txt");
	ofstream out_file("UAH_next.txt");

	int found = 0;
	int word_count = 0;

	// Read in the file
	string line;
	string working;
	string bigfile = "";
	while(in_file.good()) {
		getline(in_file, line);

		// replace UAH with UAHuntsville
		found = line.find("UAH");
		while(found != string::npos) {
			line.replace(found, 3, "UAHuntsville");
			found = line.find("UAH", found + 1);
		}

		out_file << line << endl;

		bigfile += line;
	}

	// reopen the bad boy
	in_file.close();
	in_file.open("UAH_sample.txt");
	while(in_file >> working) { word_count++; }

	cout << "Number of words: " << word_count << endl;

	in_file.close();
	out_file.close();

	system("pause");

	return 0;
}
