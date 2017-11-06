#include <iostream>

char get_block(std::istream &stream);
int put_block(char block, int position, char array[]);
int shift_right(int position);
int shift_left(int position);
bool compare_blocks(char robot, char in_slot);
char switch_blocks(char robot, int position, char array[]);
bool test_empty(int position, char array[]);
