#include <iostream>

using namespace std;

// ------------------------------------------------------------------------ //
//																			//
//																			//
//				Functions for the seven robot operations					//
//																			//
//																			//
// ------------------------------------------------------------------------ //

//
// Function get_block
// Reads in a single character value from the keyboard 
// This is the input from the chute
// Returns: a single character
//
// Example function call: 	block = get_block();

// <<Edited>>
char get_block(std::istream &stream)
{
	char block;
	stream >> block;
	return block;
}

// Function put_block
// This function stores a character into the character array representing the slots
//
// Inputs: 
// block - type char - The character to be inerted into a slot
// position - type int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// position - type int - the index of the slot where the block was placed
//
// Example function call: 	put_block(block, position, slots);

int put_block(char block, int position, char array[])
{
	array[position] = block;
	cout << "Block " << block << " inserted into slot " << position << endl;
	return position;
}

// Function shift_right
// This function increments the index simulating a movement of the robot 
// to the next higher slot (index) of the array
// 
// Inputs:
// position - type int - current slot position
//
// Returns:
// position - type int - The updated position which is input position + 1
//
// Example function call:  position = shift_right(position)
//

int shift_right(int position)
{
	position++;
	cout << "Position right shifted to " << position << endl;
	return position;
}

// Function shift_left
// This function decrements the index simulating a movement of the robot 
// to the next lower slot (index) of the array
// 
// Inputs:
// position - type int - current slot position
//
// Returns:
// position - type int - The updated position which is input position - 1
//
// Example function call: position = shift_left(position)
//

int shift_left(int position)
{
	position--;
	cout << "Position left shifted to " << position << endl;
	return position;
}

// Function compare_blocks
// This function compares the value of the block held by the robot 
// with the value of the block in a slot 
// 
// Inputs:
// robot - type char - value of block held by robot
// in_slot - type char - value of block in the slot
bool compare_blocks(char robot, char in_slot)
{
	
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
// Function switch_blocks
// This function switches the block held by the robot with a block in a slot. 
// After the switch the robot is holding the block removed from the slot.
// 
// Inputs: 
// robot - type char - The block to be inserted into a slot
// position - type int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// robot - type char. The value of the block removed from the slot.
//
// Example function call: block = switch_blocks(block,  position, array);
//

char switch_blocks(char robot, int position, char array[])
{
	char temp_hold;

	cout << "Switching blocks " << robot << " with " << array[position] << endl;
	temp_hold = robot;
	robot = array[position];
	array[position] = temp_hold;
	return robot;
}
// Function test_empty
// This function tests the array to determine if a slot is empty (NULL) 
// 
// Inputs:
// position - type int - index of slot to be tested
//
// Returns:
// true or false as value o function
// TRUE if slot is empty
// FALSE if the slot contains a block
//
// Example function call: if ( test_empty(index, array) )
//
bool test_empty(int position, char array[])
{
	if  (array[position] == 0)
	{
		cout << "Slot " << position << " empty. " << endl;
		return true;
	}
	else
	{
		cout << "Slot " << position << " contains a block " << endl;
		return false;
	}

}