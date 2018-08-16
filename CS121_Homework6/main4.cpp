#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

struct timeS
{
	unsigned int hour;
	unsigned int minutes;
	unsigned int seconds;
};

struct date 
{
	unsigned int month;
	unsigned int day;
	unsigned int year;
};

struct location
{
	double longi, lati, alti;
};

struct stationData {
	unsigned int hour;
	unsigned int minutes;
	unsigned int seconds;
	double temp, windSpeed, bPressure, precip;
};
ostream& operator<<(ostream& out, const stationData& sd)
{
   return out << sd.hour << ':' << sd.hour  << ':' << sd.seconds  << ' ' << sd.temp << ' ' << 
   			  << sd.windSpeed << ' ' << sd.bPressure << ' '  << sd.precip;
}

struct portableStation
{
	stationData data[24];
	date recordDate;
	location recordLocation;
};

void findDate (portableStation &stationData){
	ifstream *infile;
	infile;
}

void findLocation (string stationFile, portableStation &stationData){
	stationFile[3]

}


int main() {

	int i = 0, counter = 0;
	string hold;
	portableStation stationRecord;
	char ch1 = ' ';

	ifstream infile;
	infile.open("C:/Users/CodySanders/Documents/CS121/wsd.txt");

	if (infile.good()){
		cout << "File was opened for reading!" << endl;
	}
	else {
		cout << "Damn it, batman!" << endl;
	}

	getline(infile, hold);	
	infile >> hold;
	infile >> stationRecord.recordDate.month;
	infile >> stationRecord.recordDate.day;
	infile >> stationRecord.recordDate.year;

	infile >> hold >> hold;
	infile >> stationRecord.recordLocation.longi;
	infile >> hold;
	infile >> stationRecord.recordLocation.lati;
	infile >> hold;
	infile >> stationRecord.recordLocation.alti;

	getline(infile, holdA);	
	getline(infile, holdA);	

	i = 0;
	while (infile.good()){
		infile >> stationRecord.data[i].hour;
		infile.ignore(1);
		infile >> stationRecord.data[i].hour;
		infile.ignore(1);
		infile >> stationRecord.data[i].hour;
		infile >> stationRecord.data[i].temp;
		infile >> stationRecord.data[i].windSpeed;
		infile >> stationRecord.data[i].bPressure;
		infile >> stationRecord.data[i].precip;

		i++;
	}









	return 0;
	system("pause");
}
