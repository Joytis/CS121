#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char ** argv) {

	// vars
	float celc;
	float faren;
	float kelvin;

	// Files
	ifstream in_file("temps.txt");
	ofstream out_file("temp_table.txt");

	// header
	out_file << left;
	out_file << setw(20) << "Celsuis";
	out_file << setw(20) << "Fahrenheit";
	out_file << setw(20) << "Kelvin" << endl;


	while(in_file.good()) {
		// Process each line of file and stuff it up in there. 
		in_file >> celc;
		faren = (9/5) * celc + 32;
		kelvin = celc + 273;

		out_file << setw(20) << celc; 
		out_file << setw(20) << faren; 
		out_file << setw(20) << kelvin << endl; 
	}

	// Clean it up, boy. 
	in_file.close();
	out_file.close();

	return 0;
}
