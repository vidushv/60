#include <iostream>
#include <fstream>
#include "LinkedList.h"

using namespace std;

void RunList(char *);


int main ()
{
	return 0;

}

int getChoice()
{
  
	int userChoice;
	cout << "      ADT Menu" << endl;
	cout << "0. Quit" << endl;
	cout << "1. LinkedList" << endl;
	cout << "2. CursorList" << endl;
	cout << "3. StackAr" << endl;
	cout << "4. StackLi" << endl;
	cout << "5. QueueAr" << endl;
	cout << "6. SkipList" << endl;
	cout << "Your choice >> ";
	cin >> userChoice;
}


void RunList (char *filename)
{
	List<int> list;
	ListItr<int> listItr = list.zeroth();
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value)
	{
		if (comm == 'i')
			list.insert(value, listItr);
		else
			list.remove(value);
	}		
}	
