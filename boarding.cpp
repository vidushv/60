#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"

using namespace std;

class Passenger{
	int seatNumber;
	char seat;

public:
	Passenger(): seatNumber(0), seat('A') {}
	Passenger(int n, char s): seatNumber(n), seat(s) {}
	//Passenger(const Passenger& p): seatNumber(p.seatNumber), seat(p.seat) {}

};

class Row{
	StackAr<Passenger> leftAisle;
	StackAr<Passenger> RightAisle;

	StackAr<Passenger> passengersStanding;
	Passenger aislePassenger;
};

Queue<Passenger> readPassengers(char *filename)
{
	Queue<Passenger> passengers (288);
	ifstream inf(filename);

	int number;
	char seat;

	for (int i = 0; i < 288; i++)
	{
		inf >> number >> seat;
		Passenger p(number, seat);
		passengers.enqueue(p);

	}

	inf.close();

	return passengers;

}

int main(int argc, char** argv)
{
	char* file = argv[1];

	Queue<Row> rows(48);
	Queue<Passenger> passengers;
	passengers = readPassengers(file);

	return 0;
}


