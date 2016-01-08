#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"

using namespace std;

enum State {EMPTY, RIGHT_ROW, WRONG_ROW, STORING_LUGGAGE1, STORING_LUGGAGE2};

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
    State state;
    Passenger aislePassenger;
  	StackAr<Passenger> leftAisle;
  	StackAr<Passenger> rightAisle;
  	StackAr<Passenger> passengersStanding;

public:

    State getState() const {return state;}
    void setState(State stat) {state = stat;}
    void setPassenger(Passenger p) {aislePassenger = p;}
    int getNumber() const {return rowNumber;}

    Row (): rowNumber(-1), state(EMPTY) {}
	  Row(int number): rowNumber(number), state(EMPTY)
	{
		leftAisle = StackAr<Passenger> (3);
		rightAisle = StackAr<Passenger> (3);
		passengersStanding = StackAr<Passenger> (2);
	}

    void lastStep()
    {
        switch (state)
        {
            case EMPTY:
                break;

            case RIGHT_ROW:
                state = STORING_LUGGAGE1;
                break;

            case WRONG_ROW:
                break;

            case STORING_LUGGAGE1:
                state = STORING_LUGGAGE2; 
                break;

            case STORING_LUGGAGE2:
                switch (aislePassenger.getSeat())
                {
                    case 'A':
                    case 'B':
                    case 'C':
                        leftAisle.push(aislePassenger);
                        state = EMPTY;
                        break;
                    case 'D':
                    case 'E':
                    case 'F':
                        rightAisle.push(aislePassenger);
                        state = EMPTY;
                        break;
                }
        }

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
                    state = EMPTY;
                }
                break;

			case STORING_LUGGAGE1:
				state = STORING_LUGGAGE2; break;
			case STORING_LUGGAGE2:
                switch (aislePassenger.getSeat())
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
                state = EMPTY;
		}
	}
    friend ostream& operator << (ostream& os, Row& row);
};

ostream& operator << (ostream& os, Row& row)
{
    switch (row.state)
    {
        case EMPTY: 
            cout << "E";
            break;
        case RIGHT_ROW: 
            cout << "R";
            break;
        case WRONG_ROW:
            cout << "W"; 
            break;
        case STORING_LUGGAGE1:
        case STORING_LUGGAGE2:
            cout << "S";
            break;
    }
    return os;
}

class Plane
{
    Queue<Passenger> passengers;
    Queue<Row> rows;
public:
    Plane(Queue<Passenger>& pass): passengers(pass)
    {
        rows = Queue<Row>(48);
        for (int i = 48; i >= 1; i--)
        {
            Row row(i);
            rows.enqueue(row);
        }
    }

    void step()
    {
        Row next_row = rows.dequeue();
        Row curr_row;
        next_row.lastStep();

        for (int i = 0; i < 47; i++)
        {
            curr_row = rows.dequeue();
            curr_row.step(next_row);
            rows.enqueue(next_row);
            next_row = curr_row;
        }

        if (curr_row.getState() == EMPTY && !passengers.isEmpty())
        {
            Passenger p = passengers.dequeue();
            curr_row.setPassenger(p);
            if (p.getNumber() == curr_row.getNumber())
              curr_row.setState(RIGHT_ROW);
            else
              curr_row.setState(WRONG_ROW);
        }
        rows.enqueue(curr_row);
    }

    friend ostream& operator << (ostream& os, Plane& plane);

    bool isDone()
    {
        if (!passengers.isEmpty())
            return false;

        for (int i = 0; i < 48; i++)
        {
            Row row = rows.dequeue();
            if (row.getState() != EMPTY)
                return false;
            rows.enqueue(row);
        }
        
        return true;
    }

    void board()
    {
      int timer = 0;
      while (!isDone())
      {
        timer += 5;
        step();
        cout << timer << " " << *this << endl;
      }
    }


};

ostream& operator << (ostream& os, Plane& plane)
{
    for (int i = 0; i < 48; i++)
    {
        Row row = plane.rows.dequeue();
        cout << row;
        plane.rows.enqueue(row);
    }

    return os;
}

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

	Queue<Passenger> passengers;
	passengers = readPassengers(file);
  Plane plane(passengers);

  plane.board();

	return 0;
}


