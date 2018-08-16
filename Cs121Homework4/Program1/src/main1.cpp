#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

template<typename F>
void bubble_sort(string &str, F cmp) {
	char tmp;
	for(int i = str.size() - 2; i > 0; i--){
		for(int j = 0; j <= i; j++){
			if(cmp(str[j], str[j+1])) {
				tmp = str[j];
				str[j] = str[j+1];
				str[j+1] = tmp;
			}
		}
	}
}

template<typename F>
void selection_sort(string &str, F cmp) {
	size_t store_pos;
	char temp;
	for(size_t i = 0; i < str.size() - 1; i++) {
		store_pos = i;
		for(size_t j = i; j < str.size(); j++) {
			if(cmp(str[store_pos], str[j])) {
				store_pos = j;
			}
		}
		temp = str[store_pos];
		str[store_pos] = str[i];
		str[i] = temp;
	}
}

int main() {
	// NOTE(clark): just kind of ignoring spaces for now. 
	// Prompt and input
	cout << "Please enter a string: ";
	string input;
	getline(cin, input);

	// Make lowercase
	for(char & c : input) {
		c = tolower(c);
	}

	// Pass comparison functions to the sorting algorithms
	string test(input);
	bubble_sort(test, [](char first, char second) -> bool {
		return first > second;
	});
	cout << test << endl;

	// Pass comparison functions to the sorting algorithms
	string test2(input);
	selection_sort(test2, [](char first, char second) -> bool {
		return first < second;
	});
	cout << test2 << endl;
}