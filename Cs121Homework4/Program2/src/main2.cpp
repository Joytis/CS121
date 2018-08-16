// 1. Design and write a program that will accept a sentence as 
// input, reverse the words and print the sentence out backwards. 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

using storage = std::vector<string>;

template<typename F>
void bubble_sort(storage &vec, F callable) {
	string tmp;
	for(int i = vec.size() - 2; i > 0; i--){
		for(int j = 0; j <= i; j++){
			if(callable(vec[j], vec[j+1])) {
				tmp = vec[j];
				vec[j] = vec[j+1];
				vec[j+1] = tmp;
			}
		}
	}
}	

int main() {
	storage store;
	string temp;
	ifstream infile("pgrm2_input.txt");
	ofstream outfile("pgrm2_sorted.txt");

	if(!infile.good()) {
		cout << "Please enter a valid file name" << endl;
		return -1;
	}

	while(infile.good()) {
		infile >> temp;
		store.push_back(temp);
	}

	// Using copy constructors because I want lower-case. 
	bubble_sort(store, [](string first, string second) -> bool{
		// Lower case strings
		for(char &c: first) c = tolower(c);
		for(char &c: second) c = tolower(c);

		return (first.compare(second) > 0);
	});

	int count = 0;
	for(string &s : store) {
		if(count++ == 9){
			outfile << '\n';
			count = 0;
		}
		outfile << s << " ";
	}

}