// 1. Design and write a program that will accept a sentence as 
// input, reverse the words and print the sentence out backwards. 

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>

#include "functionlib.hpp"

using namespace std;
using map = std::unordered_map<char, int>;

// NOTE(clark): Originally, I thought that sorting the values on the fly was the correct solution
//				to this problem of minimum calls to 'swap_block. However, this is very much not 
// 				the case. The robot has the ability to process information outside its immidiate
//				action, or else it would not be able to keep track of its place in whatever sorting
//				algorithm currently being run. Therefore, the prompt allows we store information
//				external to the currently held block. 
//					This being the case, the way to minimise the base operation is thereby to 
//				storing the array in 'memory', sorting the array in 'memory', and then reconstructing 
//				the blocks in the 'physical' array of blocks to resemble the sorted memory array. 
//				This cuts down on ALL extraneous swaps assuming that each swap places a block in the 
//				correct position. This may not be true for all cases, but we can try our best.
// 					Furthermore, we can cut down on MORE swap_block calls if we do a kind of 'predictive
//				placement'. Considering there is only 20 slots for our robot and the blocks are in 
//				alphabetical order, we can place there blocks where we could /expect/ them to be 
//				alphabetically. 
// 					Now, this means that the sorting algorithm is completely irrelavent to optimizing
//				the problem, considering we are sorting it before we even touch a block. This 
//				considered, I chose quicksort because it makes me feel good. 

// Little macro for size. 
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// Yay. Quicksort. 
void quicksort(char arr[], int left, int right);
void robot_move_difference(int &position, int end);
char swap_and_count(char robot, int position, char array[], int &count);
int expand_range(int pos, char store[]);



int main(int argc, char **argv) {

	// Using this as a predictive indexing for the array.
	// Will probably cut down on swap operations.  
	// NOTE(clark): This could totally be represented by an array. BUt this is just so much 
	//				cleaner.
	map char_map = {
		{'a', 0}, {'b', 1}, {'c', 1}, {'d', 2}, {'e', 2}, {'f', 3},
		{'g', 4}, {'h', 5}, {'i', 6}, {'j', 7}, {'k', 8}, {'l', 9},
		{'m', 10}, {'n', 11}, {'o', 12}, {'p', 13}, {'q', 14}, {'r', 14},
		{'s', 15}, {'t', 16}, {'u', 16}, {'v', 17}, {'w', 17}, {'x', 17},
		{'y', 19}, {'z', 19}
	};

	// Always 20 blocks stored. 
	char block_storage[20] = {}; 
	char sort_storage[20] = {};
	char block_memory[20] = {};


	// We want the program and the name of the file to open. 
	if(argc != 2) {
		cout << "Please enter a file to sort." << endl;
		return -1;
	}

	string line;
	ifstream infile(argv[1]);
	// Check for valid file. 
	if(!infile.good()) {
		cout << "Invalid File Name." << endl;
		return -1;
	}

	// Get all those blocks! Wow!
	while(infile.good()) {
		// Stuff the blocks into the block array and RECORD their values in ref array
		char input = tolower(get_block(infile));
		int predict = char_map[input];

		// Check for collision
		if(block_storage[predict] != 0) {
			predict = expand_range(predict, block_storage);
		}

		// Put the block in the ACTUAL BLOCK ARRAY
		put_block(input, predict, block_storage);

		// Put put the 'value' in the SORTED STORAGE
		sort_storage[predict] = input;
		// Put put the 'value' in the UNSORTED STORAGE
		block_memory[predict] = input;
	}


	// We don't care about the blocks right now. Sort the reference. 
	quicksort(sort_storage, 0, ARRAY_SIZE(sort_storage) - 1);

	//=================================================================
	// Actual Robot Code
	//=================================================================
	int swap_times = 0;
	int position = 0;
	char robot = ' ';

	// Here's where we sort 
	for(int i = 0; i < (int)ARRAY_SIZE(block_storage) - 1; i++) {
		// If we know the block is sorted, chill. 
		if(block_memory[i] == sort_storage[i]) {
			continue;
		}

		robot_move_difference(position, i);
		robot = swap_and_count(robot, position, block_storage, swap_times);

		// NOTE(clark): This could be condensed. 
		// Search optimistically for a block with the same value to swap

		// Search for the correctly sorted block. It WILL exist. 
		for(int j = i + 1; j < (int)ARRAY_SIZE(block_storage); j++) {

			if(block_memory[j] == sort_storage[i]){
				robot_move_difference(position, j);
				// Update the memory
				block_memory[j] = robot;
				robot = swap_and_count(robot, position, block_storage, swap_times);
				robot_move_difference(position, i);
				// Update the memory
				block_memory[i] = robot;
				robot = swap_and_count(robot, position, block_storage, swap_times);
				break;
			}
		}

		// TRY TO ENSURE ROBOT IS EMPTY AT END OF LOOP. 
	}	

	// print values. 
	for(int i = 0; i < (int)ARRAY_SIZE(sort_storage); i++){
		cout << block_storage[i];
	}
	cout << " " << swap_times << endl;

	return 0;
}

void robot_move_difference(int &position, int end) {
	int diff = position - end;
	if(diff < 0) {
		diff *= -1;
		while(diff-- > 0) {
			position = shift_right(position);
		}
	}
	else {
		while(diff-- > 0) {
			position = shift_left(position);
		}
	}
}

char swap_and_count(char robot, int position, char array[], int &count) {
	count++;
	return switch_blocks(robot, position, array);
}

// This is not efficient or good. I'm just moving fast. 
int expand_range(int pos, char store[]) {

	int i = pos + 1;
	int j = pos - 1;
	while(true){
		if(i < 20) {
			if(store[i] == 0) 
				return i;
			i++;
		}
		if(j >= 0){
			if(store[j] == 0) 
				return j;
			j--;
		}
		if(i >= 20 && j < 0) {
			break;
		}
	}

	return -1;
}


// Classic quicksort right here. 
void quicksort(char arr[], int left, int right)
{
	int i = left;
	int j = right;
	char tmp;

	// set quicksort pivot at half, I guess. 
	int pivot_pos = (left + right) / 2;
	char pivot = arr[pivot_pos];

	// Main partition loop
	while (i <= j) {
		// Check if things have already been partitioned(left)
		while (arr[i] < pivot){
			i++;
		}
		// Check if things have already been partitioned (right)
		while (arr[j] > pivot)
			j--;
		// Swap the values that are < and > than pivot. 
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;

			// move on our merry little way. 
			i++;
			j--;
		}
	}

	// Recursive partitioning. 
	if (j > left)
		// leftwards partition.
		quicksort(arr, left, j);
	if (i < right)
		// Rightwards partition.
		quicksort(arr, i, right);
}

