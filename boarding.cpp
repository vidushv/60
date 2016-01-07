#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"

using namespace std;

class Passenger{
	int seatNumber;
	char seat;

public:
    int getNumber() const {return seatNumber;}
    char getSeat() const {return seat;}
	Passenger(): seatNumber(0), seat('A') {}
	Passenger(int n, char s): seatNumber(n), seat(s) {}
	Passenger(const Passenger& p): seatNumber(p.seatNumber), seat(p.seat) {}

};

class Row{
    int rowNumber;
	StackAr<Passenger> leftAisle;
	StackAr<Passenger> rightAisle;

	StackAr<Passenger> passengersStanding;
	Passenger aislePassenger;

	enum State {EMPTY, RIGHT_ROW, WRONG_ROW, STORING_LUGGAGE1, STORING_LUGGAGE2};
	State state;

public:

    State getState() const {return state;}
    void setState(State stat) {state = stat;}
    void setPassenger(Passenger& p) {aislePassenger = p;}
    int getNumber() const {return rowNumber;}

	Row(int number): rowNumber(number), state(EMPTY), aislePassenger(NULL)
	{
		leftAisle = StackAr<Passenger> (3);
		rightAisle = StackAr<Passenger> (3);
		passengersStanding = StackAr<Passenger> (2);
	}

	void step(Row& next_row)
	{
		switch (state)
		{
			case EMPTY:
                break;

			case RIGHT_ROW:
				state = STORING_LUGGAGE1;
                break;

			case WRONG_ROW:
                if (next_row.getState() == EMPTY)
                {
                    if (aislePassenger.getNumber() == next_row.getNumber())
                        next_row.setState(RIGHT_ROW);
                    else
                        next_row.setState(WRONG_ROW);

                    next_row.setPassenger(aislePassenger);
                    aislePassenger = NULL;
                    state = EMPTY;
                }
                break;

			case STORING_LUGGAGE1:
				state = STORING_LUGGAGE2; break;
			case STORING_LUGGAGE2:
                switch aislePassenger.getNumber()
                {
                    case 'A':
                    case 'B':
                    case 'C':
                        leftAisle.push(aislePassenger);
                        break;
                    case 'D':
                    case 'E':
                    case 'F':
                        rightAisle.push(aislePassenger);
                        break;
                }
		}

	}

};

class Plane
{
    Queue<Row> rows;
public:
    Plane()
    {
        rows = Queue<Row>(48);
        for (int i = 48; i >= 1; i--)
        {
            Row row(i);
            rows.enqueue(row);
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


