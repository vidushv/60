#include <iostream>
#include <fstream>
#include "QueueAr.h"
#include "StackAr.h"

using namespace std;

class Row{
	StackAr<passenger> leftAisle(3);
	StackAr<passenger> RightAisle(3);

	stackAr<passenger> passengersStanding(3);
	stackAr<passenger> aislePassenger(3);
};

class passenger{


};

int main(int argc, char** argv)
{
	QueueAr<Row> rows(48);
	
	return 0;
}


