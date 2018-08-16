#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

struct hms_time {
	int hour;
	int minute;
	int second;
};

struct station_data {
	hms_time time;
	float temp;
	float wind_speed;
	float pressure;
	float precip;
};

struct daily_data {
	int month;
	int day;
	int year;
	float lat;
	float lon;
	int altitude;
	vector<station_data> data;
};

void read_daily_data(daily_data &dd, istream &stream);
void print_station_data(const station_data &sd);

int main(int argc, char ** argv) {	 

	if(argc != 2) {
		cout << "Please enter a file for input!" << endl;
		return 0;
	}

	ifstream infile(argv[1]);
	if(!infile.good()) {
		cout << "Cannot open input file" << endl;
		return 0;
	}

	daily_data day_data;
	read_daily_data(day_data, infile);

	if(day_data.data.empty()) {
		cout << "No data to process in file. Or it was corrupted" << endl;
		return 0;
	}

	// Do some computations on the data. 
	station_data *high_temp = &day_data.data[0];		
	station_data *low_temp = &day_data.data[0];
	station_data *max_wind = &day_data.data[0];
	float total_precip = 0.0;
	for(station_data &sd : day_data.data) {

		// Check for high tempreature
		if(sd.temp > high_temp->temp) {
			high_temp = &sd;
		}

		// Check for low temp;
		if(sd.temp < low_temp->temp) {
			low_temp = &sd;
		}

		// Check for wind speed
		if(sd.wind_speed > max_wind->wind_speed) {
			max_wind = &sd;
		}

		total_precip += sd.precip;
	}

	cout << "HIGHEST TEMPREATURE: \n===============================" << endl;
	print_station_data(*high_temp);
	cout << endl << "LOWEST TEMPREATURE: \n===============================" << endl;
	print_station_data(*low_temp);
	cout << endl << "HIGHEST WIND SPEED: \n===============================" << endl;
	print_station_data(*max_wind);

	cout << endl << "Total Precipitation: " << total_precip << endl;

	return 0;
}

// Read from the stream as if it hasn't been touched yet. 
void read_daily_data(daily_data &dd, istream &stream) {
	string line;
	string temp;
	// Ignore first line.
	getline(stream, line);

	// NOTE(clark): Any occurrance of 'temp' in these statements is just ignored words. 
	// pop off date
	stream >> temp >> dd.month >> dd.day >> dd.year;
	// pop off header info
	stream >> temp >> temp >> dd.lat >> temp >> dd.lon >> temp >> dd.altitude;

	// Pop end of line and next line off stream
	getline(stream, line);
	getline(stream, line);

	// Read all the data from stream.
	while(stream.good()) {
		station_data sd;

		// Grab all the lines from the file and store them in the data. 
		stream >> sd.time.hour;
		stream.ignore(1);
		stream >> sd.time.minute;
		stream.ignore(1);
		stream >> sd.time.second;
		stream >> sd.temp >> sd.wind_speed >> sd.pressure >> sd.precip;

		dd.data.push_back(std::move(sd));
	}
}

void print_station_data(const station_data &sd) {
	cout << "Time: " << sd.time.hour << ":" << sd.time.minute << ":" << sd.time.second << endl;
	cout << "Tempreature: " << sd.temp << endl;
	cout << "Wind Speed: " << sd.wind_speed << endl;
	cout << "Pressure: " << sd.pressure << endl;
	cout << "Precipitation: " << sd.precip << endl;
}
