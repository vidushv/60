#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"

using namespace std;

enum State {EMPTY, RIGHT_ROW, WRONG_ROW, STORING_LUGGAGE1, STORING_LUGGAGE2, LEFT_OUT, LEFT_IN, RIGHT_OUT, RIGHT_IN};

class Passenger{
	int seatNumber;
	char seat;

public:
    int getNumber() const {return seatNumber;}
    char getSeat() const {return seat;}
  	Passenger(): seatNumber(0), seat('A') {}
  	Passenger(int n, char s): seatNumber(n), seat(s) {}
  	Passenger(const Passenger& p): seatNumber(p.seatNumber), seat(p.seat) {}
};// class Passenger

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
  	}//Row constructor

    void lastStep()
    {
        switch (state) //switch based on current passenger state.
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
                switch (aislePassenger.getSeat())//switch based on passenger's seat.
                {
                    case 'A':
                        if (leftAisle.isEmpty())
                        {
                            leftAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(leftAisle.topAndPop());
                            state = LEFT_OUT;
                        }
                        break;

                    case 'B':
                        if (leftAisle.isEmpty() || leftAisle.top().getSeat() == 'A')
                        {
                            leftAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(leftAisle.topAndPop());
                            state = LEFT_OUT;
                        }
                        break;

                    case 'C':
                        leftAisle.push(aislePassenger);
                        state = EMPTY;
                        break;

                    case 'D':
                        rightAisle.push(aislePassenger);
                        state = EMPTY;
                        break;

                    case 'E':
                        if (rightAisle.isEmpty() || rightAisle.top().getSeat() == 'F')
                        {
                            rightAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(rightAisle.topAndPop());
                            state = RIGHT_OUT;
                        }
                        break;

                    case 'F':
                        if (rightAisle.isEmpty())
                        {
                            rightAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(rightAisle.topAndPop());
                            state = RIGHT_OUT;
                        }
                        break;
                }
                break;

            case LEFT_OUT:
                if (aislePassenger.getSeat() == 'A' && !leftAisle.isEmpty())
                {
                    passengersStanding.push(leftAisle.topAndPop());
                    state = LEFT_OUT;
                }//end if
                else
                {
                    leftAisle.push(aislePassenger);
                    state = LEFT_IN;
                }
                break;

            case LEFT_IN:
                leftAisle.push(passengersStanding.topAndPop());
                if (passengersStanding.isEmpty())
                {
                    state = EMPTY;
                }
                break;

            case RIGHT_OUT:
                if (aislePassenger.getSeat() == 'F' && !rightAisle.isEmpty())
                {
                    passengersStanding.push(rightAisle.topAndPop());
                    state = RIGHT_OUT;
                }//end if
                else
                {
                    rightAisle.push(aislePassenger);
                    state = RIGHT_IN;
                }
                break;

            case RIGHT_IN:
                rightAisle.push(passengersStanding.topAndPop());
                if (passengersStanding.isEmpty())
                {
                    state = EMPTY;
                }
                break;
                
        }//end switch

    }//lastStep()

	void step(Row& next_row)
	{
		switch (state) //switch based on current row state.
		{
			case EMPTY:
                break;

			case RIGHT_ROW:
				state = STORING_LUGGAGE1;
                break;

			case WRONG_ROW:
                if (next_row.getState() == EMPTY)//if the next row is empty.
                {
                    if (aislePassenger.getNumber() == next_row.getNumber())//if the next row is correct.
                        next_row.setState(RIGHT_ROW);
                    else //if the next row is wrong.
                        next_row.setState(WRONG_ROW);

                    next_row.setPassenger(aislePassenger);
                    state = EMPTY;
                }//end if
                break;

			case STORING_LUGGAGE1:
				state = STORING_LUGGAGE2; break;
			case STORING_LUGGAGE2:
                switch (aislePassenger.getSeat())//switch based on passenger's seat.
                {
                    case 'A':
                        if (leftAisle.isEmpty())
                        {
                            leftAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(leftAisle.topAndPop());
                            state = LEFT_OUT;
                        }
                        break;
                    case 'B':
                        if (leftAisle.isEmpty() || leftAisle.top().getSeat() == 'A')
                        {
                            leftAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(leftAisle.topAndPop());
                            state = LEFT_OUT;
                        }
                        break;
                    case 'C':
                        leftAisle.push(aislePassenger);
                        state = EMPTY;
                        break;
                    case 'D':
                        rightAisle.push(aislePassenger);
                        state = EMPTY;
                        break;
                    case 'E':
                        if (rightAisle.isEmpty() || rightAisle.top().getSeat() == 'F')
                        {
                            rightAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(rightAisle.topAndPop());
                            state = RIGHT_OUT;
                        }
                        break;
                    case 'F':
                        if (rightAisle.isEmpty())
                        {
                            rightAisle.push(aislePassenger);
                            state = EMPTY;
                        }
                        else
                        {
                            passengersStanding.push(rightAisle.topAndPop());
                            state = RIGHT_OUT;
                        }
                        break;
                }
                break;

            case LEFT_OUT:
                if (aislePassenger.getSeat() == 'A' && !leftAisle.isEmpty())
                {
                    passengersStanding.push(leftAisle.topAndPop());
                    state = LEFT_OUT;
                }//end if
                else
                {
                    leftAisle.push(aislePassenger);
                    state = LEFT_IN;
                }
                break;
                
            case LEFT_IN:
                leftAisle.push(passengersStanding.topAndPop());
                if (passengersStanding.isEmpty())
                {
                    state = EMPTY;
                }
                break;

            case RIGHT_OUT:
                if (aislePassenger.getSeat() == 'F' && !rightAisle.isEmpty())
                {
                    passengersStanding.push(rightAisle.topAndPop());
                    state = RIGHT_OUT;
                }//end if
                else
                {
                    rightAisle.push(aislePassenger);
                    state = RIGHT_IN;
                }
                break;

            case RIGHT_IN:
                rightAisle.push(passengersStanding.topAndPop());
                if (passengersStanding.isEmpty())
                {
                    state = EMPTY;
                }
                break;
		}//end switch
	}//step()
    friend ostream& operator << (ostream& os, Row& row);
};// class Row

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
        case LEFT_IN:
        case RIGHT_IN:
            cout << "I";
            break;
        case LEFT_OUT:
        case RIGHT_OUT:
            cout << "O";
            break;

    }
    return os;
}//operator << 

class Plane
{
    Queue<Passenger> passengers;
    Queue<Row> rows;
public:
    Plane(Queue<Passenger>& pass): passengers(pass)
    {
        rows = Queue<Row>(48);
        for (int i = 48; i >= 1; i--)//iterate through every row from end to beginning.
        {
            Row row(i);
            rows.enqueue(row);
        }// end for
    }//Plane constructor.

    void step()
    {
        Row next_row = rows.dequeue();
        Row curr_row;
        next_row.lastStep();

        for (int i = 0; i < 47; i++)//for every row, except the last one.
        {
            curr_row = rows.dequeue();
            curr_row.step(next_row);
            rows.enqueue(next_row);
            next_row = curr_row;
        }//end for

        if (curr_row.getState() == EMPTY && !passengers.isEmpty()) //if the row and passengers are not empty.
        {
            Passenger p = passengers.dequeue();
            curr_row.setPassenger(p);
            if (p.getNumber() == curr_row.getNumber()) //if the passenger is at the right row.
              curr_row.setState(RIGHT_ROW);
            else //if the passenger is at the wrong row.
              curr_row.setState(WRONG_ROW);
        }//end if
        rows.enqueue(curr_row);
    }//step

    friend ostream& operator << (ostream& os, Plane& plane);

    bool isDone()
    {
        if (!passengers.isEmpty()) //if any passenger has not boarded.
            return false;

        bool notDone = false;

        for (int i = 0; i < 48; i++) // for every row.
        {
            Row row = rows.dequeue();
            if (row.getState() != EMPTY)//if the row contains people.
                notDone = true;
            rows.enqueue(row);
        }//end for
        
        if (notDone) //if boarding is not complete.
            return false;
        else //if boarding is complete.
            return true;
    }//isDone()

    void board()
    {
      int timer = 0;
      while (!isDone()) //until boarding is complete.
      {
        timer += 5;
        step();
      }//end while.
      cout << timer << endl;
    }//board()


};//Class Plane

ostream& operator << (ostream& os, Plane& plane)
{
    for (int i = 0; i < 48; i++) // for every row
    {
        Row row = plane.rows.dequeue();
        cout << row;
        plane.rows.enqueue(row);
    }

    return os;
}// operator << 

Queue<Passenger> readPassengers(ifstream& inf)
{
	Queue<Passenger> passengers (288);

	int number;
	char seat;

	for (int i = 0; i < 288; i++) // for every passenger
	{
		inf >> number >> seat;
		Passenger p(number, seat);
		passengers.enqueue(p);

	}//end for

	return passengers;

}//readPassengers()

int main(int argc, char** argv)
{
	char* file = argv[1];
    ifstream inf(file);

	Queue<Passenger> passengers1 = readPassengers(inf), passengers2 = readPassengers(inf), passengers3 = readPassengers(inf);

    inf.close();

    Plane plane1(passengers1), plane2(passengers2), plane3(passengers3);
    cout << "Back to front: ";
    plane1.board();
    cout << "Random: ";
    plane2.board();
    cout << "Outside in: ";
    plane3.board();

	return 0;
}//main()


