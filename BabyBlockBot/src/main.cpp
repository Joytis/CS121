#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;
using map = std::unordered_map<char, int>;

// Little macro for size. 
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// Yay. Quicksort. 
void quicksort(char arr[], int left, int right);
void robot_move_to(int &position, int end);
char swap_and_count(char robot, int position, char array[], int &count);
int expand_range(int pos, char store[]);


// function libb

char get_block(std::istream &stream);
int put_block(char block, int position, char array[]);
int shift_right(int position);
int shift_left(int position);
bool compare_blocks(char robot, char in_slot);
char switch_blocks(char robot, int position, char array[]);
bool test_empty(int position, char array[]);

#define MAX_BLOCKS (20)

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
	char block_storage[MAX_BLOCKS] = {};
	// NOTE(clark): I'm not sure if VS2012 automatically initializes empty initializer
	//				list stuff to 0, so i'm just setting it here. 
	for(int i = 0; i < ARRAY_SIZE(block_storage); i++) {
		block_storage[i] = 0;
	} 

	// We want the program and the name of the file to open. 
	if(argc != 2) {
		cout << "Please enter a file to read." << endl;
		return -1;
	}

	string line;
	ifstream infile(argv[1]);
	// Check for valid file. 
	if(!infile.good()) {
		cout << "Invalid File Name." << endl;
		return -1;
	}

	// Robot reading code
	//=============================
	char robot = 0;
	int swap_count = 0;
	int position = 0;
	int swap_position = 0;
	
	// Just a quick toggle for filing to the right or left. 
	// right is true, left is false
	bool fill_direction = false;

	// DO NOT EXCEED MAX OF 20 BLOCKS
	int count = 0;
	// Get all those blocks! Wow!
	while(infile.good() && (count++ < MAX_BLOCKS)) {
		// Stuff the blocks into the block array and RECORD their values in ref array
		robot = (char)tolower(get_block(infile));

		// Move robot arm to predicted position
		robot_move_to(position, char_map[robot]);

		// Check for collision. If there is, time to shift things around. 
		if(!test_empty(position, block_storage)) {

			// Find a position to swap at
			//=======================================================================
			// If we're less than the block, we should be leftwards from it
			if(compare_blocks(robot, block_storage[position])){
				fill_direction = false;
				// Continue until a block is found greater than block or out of range
				while(compare_blocks(robot, block_storage[position]) && position != 0){
					// If the space is empty, then we're done regardless
					if(test_empty(position, block_storage)) break;
					robot_move_to(position, position - 1);
				}
				// If we're at the end of the rope, reverse shift direction
				if(position == 0) {
					fill_direction = true;
					if(!compare_blocks(robot, block_storage[position])) {
						robot_move_to(position, 1);
					}
				}
			}
			// If we're greater than the block, we should be rightwards from it
			else{
				fill_direction = true;
				// continue until find block less than char or at max
				while(!compare_blocks(robot, block_storage[position]) && position != 19){
					// If we're at the end of the rope, reverse shift direction and break
					// If the space is empty, then we're done regardless
					if(test_empty(position, block_storage)) break;
					robot_move_to(position, position + 1);
				}
				// If we're at the end of the rope, reverse shift direction
				if(position == 19) {
					fill_direction = false;
					// if(compare_blocks(robot, block_storage[position])) {
						// robot_move_to(position, 18);
					// }
				}
			}

			// Test if the current space is just empty. If so, just stick block here 
			//	and move on. 
			if(test_empty(position, block_storage)) {
				put_block(robot, position, block_storage);
				continue;
			}


			// The current position will be the target position for the block
			swap_position = position;
		}

		// Finally, start swapping blocks
		//=======================================================================
		// Continue swapping until the robot doesn't have anything it its hand. This
		// will happen once things have been shifted over. 
		while(robot != 0) {
			robot = swap_and_count(robot, position, block_storage, swap_count);
			if(fill_direction){
				robot_move_to(position, position + 1);
			}
			else {
				robot_move_to(position, position - 1);
			}
		}
	}

	// print values. 
	cout << endl << "===================================" << endl
		 << "RESULTS" << endl << "===================================" 
		 << endl << endl;

	for(int i = 0; i < (int)ARRAY_SIZE(block_storage); i++){
		cout << block_storage[i];
	}
	cout << " " << swap_count << endl;

	return 0;
}

void robot_move_to(int &position, int end) {
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

char get_block(std::istream &stream)
{
	char block;
	stream >> block;
	return block;
}

int put_block(char block, int position, char array[])
{
	array[position] = block;
	cout << "Block " << block << " inserted into slot " << position << endl;
	return position;
}

int shift_right(int position)
{
	position++;
	cout << "Position right shifted to " << position << endl;
	return position;
}

int shift_left(int position) {
	position--;
	cout << "Position left shifted to " << position << endl;
	return position;
}
bool compare_blocks(char robot, char in_slot) {
	
	cout << endl <<  "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
	if (robot <= in_slot)
	{
		cout << "returning true. Robot block LESS than or EQUAL to block in slot. " << endl;
		return true;
	}
	else
	{
		cout << "returning false. Robot block GREATER than block in slot. " << endl;
		return false;
	}
}

char switch_blocks(char robot, int position, char array[]) {
	char temp_hold;

	cout << "Switching blocks " << robot << " with " << array[position] << endl;
	temp_hold = robot;
	robot = array[position];
	array[position] = temp_hold;
	return robot;
}
bool test_empty(int position, char array[]) {
	if  (array[position] == 0) {
		cout << "Slot " << position << " empty. " << endl;
		return true;
	}
	else {
		cout << "Slot " << position << " contains a block " << endl;
		return false;
	}

}