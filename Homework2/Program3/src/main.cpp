#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

int main(int argc, char ** argv) {
	
	// vars
	int num_words = 0;
	int pos = 0;
	int num_chars = 0;
	string sentence;
	string working_copy;
	char char_to_find;

	// prompt
	cout << "Yo. Enter a sentence. We're gonna get weird: ";
	getline(cin, sentence);

	// If we're larger than one, we got somethign aside end of line!
	if(sentence.size() > 1) {
		num_words = 1;

		// Gotta learn those good C++ standard practices with 
		//	standard transform and lambdas!
		// NOTE(clark): Apply the lambda to everything in the string. 
		std::for_each(sentence.begin(), sentence.end(), 
			[&](char &c) {
				if(c == ' ') num_words++;
			});
	}
	// Or else we're just a end line
	else{
		num_words = 0;
	}

	// Get weird with it. 
	cout << endl << "Here's how many characters there are in that: " << sentence.size() << endl;
	cout << "Here's how many words there are in that: " << num_words << endl;

	working_copy = sentence;
	// NOTE(clark): Apply the lambda to everything in the string. 
	for_each(working_copy.begin(), working_copy.end(),
		[](auto &c) {
			// Force standard namespace to avoid C conflicts. 
			c = std::toupper(c);
		});

	cout << "Here's uppercase: " << working_copy << endl;

	// Prompt for substring stuff. 
	cout << endl << "Give me a position: ";
	cin >> pos;
	// Flush buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Prompt for substring stuff. 
	cout << "Give me a length: ";
	cin >> num_chars;
	// Flush buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if(pos + num_chars < sentence.size() && pos >= 0) {
		cout << "Here's your substring: " << sentence.substr(pos, num_chars) << endl; 
	}
	else {
		cout << "Nice try bucko. No segfaults for you." << endl;
	}

	cout << endl << "Give me a character: ";
	cin >> char_to_find;
	// Flush buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << endl;

	// I'm just going to stuff the positions in here. 
	vector<int> char_positions;

	// Show the sentence
	cout << sentence << endl;

	int temp_counter = 0;
	// Process the string. 
	for_each(sentence.begin(), sentence.end(), 
		[&](auto &c) {
			if(c == char_to_find) {
				cout << '^';
				char_positions.push_back(temp_counter);
			}
			else {
				cout << '~';
			}
			temp_counter++;
		});

	// Print where everything was. 
	cout << endl << "Positions the character was at: ";
	// Print the stuff!
	for_each(char_positions.begin(), char_positions.end(),
		[](auto &i) {
			cout << i << " ";
		});
	cout << endl;

	system("pause");

	return 0;
}
