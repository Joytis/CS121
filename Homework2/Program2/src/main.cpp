#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char ** argv) {
	
	// Vars
	string title;
	string author;
	float price;
	char y_n = 'Y';

	ofstream out_file("book_database.txt");
	// init stream
	out_file << fixed << setprecision(2) << setfill('.');

	cout << "Welcome to the cool-dude book-storing neato program!" << endl << endl;

	while(y_n == 'Y' || y_n == 'y') {

		// Get book info
		cout << "Enter Book Title: ";
		getline(cin, title);

		cout << "Enter Author: ";
		getline(cin, author);

		cout << "Enter price: ";
		cin >> price; 

		// Flush buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// Store that stuff in a file.
		out_file << left << setw(40) << title // Title 
				 << setw(20) << author 	// Author
				 << right << setw(7) << "$" << price // price
				 << endl;

		cout << endl;
		cout <<  "Yo. You want another book? (Y/N): ";
		cin >> y_n;	

		// Flush buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	out_file.close();
	return 0;
}
