#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>
#include <random>

using namespace std;

// 4
void word_scramble(const string &str);
// 5
void is_palindrome(const string &reference);
// 6
void rand_init(int array[][20], int rows, int cols, int min, int max);
void print_array(int array[][20], int rows, int cols);
void find_vals(int array[][20], int rows, int cols, int min, int max);
void min_max_avg(int array[][20], int rows, int cols, int &min, int &max, float &avg);

// 7
// Assume dimensions of array
void transpose(int array[][25]);

// 8
void uinque_init(int array[][20], int rows, int cols);


int main() {

	// Seed rng
	srand (time(NULL));

	// Test Cases: Program 4 pt 
	// String literal references
	cout << "======================================================" << endl
		 << "============   WORD SCRAMBLE TEST CASES   ============" << endl
		 << "======================================================" << endl;
	word_scramble("Coo");
	word_scramble("Cool");
	word_scramble("Peanut");
	word_scramble("Wunderlust");
	word_scramble("Wunderlustmore");

	cout << endl;

	cout << "======================================================" << endl
		 << "============   IS PALINDROME TEST CASES   ============" << endl
		 << "======================================================" << endl;
	is_palindrome("cool");
	is_palindrome("racecar");
	is_palindrome("rac1cAr");
	is_palindrome("900loOkattakooL009");
	is_palindrome("njldwnajkkkkkkkkkkkdndjkwanjkldnwjlandjklwanjkldwa");

	cout << "======================================================" << endl
		 << "============   ARRAY FUNCTIN TEST CASES   ============" << endl
		 << "======================================================" << endl;
	int test_array[20][20];
	rand_init(test_array, 20, 20, 10, 30);
	print_array(test_array, 20, 20);
	find_vals(test_array, 20, 20, 20, 25);
	int min, max;
	float avg;
	min_max_avg(test_array, 20, 20, min, max, avg);
	cout << "(min, max, avg): " << "{" << min << ", " << max << ", " << avg << "}" << endl;

	cout << "======================================================" << endl
		 << "============ TRANSPOSE +++++ TEST CASES   ============" << endl
		 << "======================================================" << endl;
	int count = 1;
	int trans_test[25][25];
	for(int i = 0; i < 25; i++)
		for(int j = 0; j < 25; j++)
			trans_test[i][j] = count++;

	cout << "Transposed data: " << endl;
	transpose(trans_test);
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			cout << setw(3) << trans_test[i][j] << " ";
		}
		cout << endl;
	}

	cout << "======================================================" << endl
		 << "============ UNIQUE RANDOM SHUFFLE TEST ==============" << endl
		 << "======================================================" << endl;
	uinque_init(test_array, 20, 20);
	print_array(test_array, 20, 20);

}	


void uinque_init(int array[][20], int rows, int cols){
	// Get random engine. 
	auto rng = std::default_random_engine {};
	vector<int> num_stack;
	for(int i = 0; i < 1000; i++) {
		num_stack.push_back(i);
	}	
	// Randomly shuffl the stack. 
	std::shuffle(num_stack.begin(), num_stack.end(), rng);

	// Init by popping values off the back of the vector
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < rows; j++) {
			array[i][j] = num_stack.back();
			num_stack.pop_back();
		}
	}
}

// Transposes the array.
void transpose(int array[][25]) {
	// Quick and simple. 
	int trans[25][25];
	// Copy it over
	for(int i = 0; i < 25; i++)
		for(int j = 0; j < 25; j++)
			trans[i][j] = array[i][j];


	// Transpose from copied array
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 25; j++){
			array[j][i] = trans[i][j];
		}
	}
}


void min_max_avg(int array[][20], int rows, int cols, int &min, int &max, float &avg) {
	int total = 0;
	min = std::numeric_limits<int>::max();
	max = std::numeric_limits<int>::min();

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(array[i][j] > max) {
				max = array[i][j];
			}	
			if(array[i][j] < min) {
				min = array[i][j];
			}	
			total += array[i][j];
		}
	}

	avg = total / (rows * cols);
}


void find_vals(int array[][20], int rows, int cols, int min, int max) {
	cout << "Data found in array: " << endl;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(array[i][j] >= min && array[i][j] <= max){
				cout << array[i][j] << ' ';
			}
		}
		cout << endl;
	}
}	

void print_array(int array[][20], int rows, int cols) {
	cout << "Data array: " << endl;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			cout << setw(3) << array[i][j] << ' ';
		}
		cout << endl;
	}
}

// CHecks if a word is a palindrome. 
void is_palindrome(const string &reference) {	
	if(reference.size() > 20) {
		cout << "String incorrect size. Size must be less than 20" << endl;
		return;
	}

	// Copy reference as lowercase
	string reference_lower(reference);
	for(char &c : reference_lower) c = tolower(c);

	// Copy reference
	string str(reference_lower);
	reverse(str.begin(), str.end());

	// Comparing 
	if(str.compare(reference_lower) == 0) {
		cout << reference << " is a palindrome :D!" << endl;
	}
	else {
		cout << reference << " is NOT a palindrome D:!" << endl;
	}
}

// Scrambles words, I guess!
void word_scramble(const string &reference) {

	if(reference.size() < 4 || reference.size() > 10) {
		cout << "String incorrect size. Size must be (4 - 10)" << endl;
		return;
	}
	// Copy the reference
	string str(reference);

	// Scramble by just rotating the letters. 
	for(size_t i = 0; i < str.size() - 1; i++) {
		str.push_back(str[0]);
		str.erase(0,1);
		cout << str << " ";
	}
	char temp = str[0];
	str[0] = *str.rbegin();
	*str.rbegin() = temp;
	cout << str << endl;
}

void rand_init(int array[][20], int rows, int cols, int min, int max) {
	for(int r = 0; r < rows; r++) {
		for(int c = 0; c < cols; c++) {
			array[r][c] = (rand() % (max - min)) + min;
		}
	}
}
