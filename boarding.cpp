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
	StackAr<Passenger> rightAisle;

	StackAr<Passenger> passengersStanding;
	Passenger aislePassenger;

	enum State {EMPTY, RIGHT_ROW, WRONG_ROW, STORING_LUGGAGE1, STORING_LUGGAGE2};
	State state;

public:
	Row(): state(EMPTY), aislePassenger(NULL)
	{
		leftAisle = StackAr<Passenger> (3);
		rightAisle = StackAr<Passenger> (3);
		passengersStanding = StackAr<Passenger> (2);
	}
	void changeState (State st)
	{
		state = st;
	}

	void step()
	{
		switch (state)
		{
			case EMPTY:

			case RIGHT_ROW:
				state = STORING_LUGGAGE1; break;
			case WRONG_ROW:

			case STORING_LUGGAGE1:
				state = STORING_LUGGAGE2; break;
			case STORING_LUGGAGE2:
		}

	}

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


