#include <iostream>
#include <fstream>
#include "CPUTimer.h"
#include "QueueAr.h"
#include "StackAr.h"
#include "StackLi.h"
#include "SkipList.h"
#include "CursorList.h"
#include "LinkedList.h"

using namespace std;

void RunList(char *);
int getChoice();

int main (int argc, char** argv)
{	
	do 
	{
		choice = getChoice();
		ct.reset();
		switch (choice)
		{
			case 1: RunList(filename); break;
			case 2: RunCursorList(filename); break;
			case 3: RunStackAr(filename); break;
			case 4: RunStackLi(filename); break;
			case 5: RunQueueAr(filename); break;
			case 6: RunSkipList(filename); break;
		} // switch

		cout << "CPU time: " << ct.cur_CPUTime() << endl;
	
	} while (choice > 0);	


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
	
	return userChoice;

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

void RunCursorList (char * filename)
{
	CursorList<int> list;
	CursorListItr<int> listItr = list.zeroth();
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

void RunStackAr (char *filename)
{
	StackAr<int> stack(250000);
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value)
	{
		if (comm == 'i')
			stack.push(value);
		else
			stack.pop();
	}		
}	

void RunStackLi (char *filename)
{
	StackLi<int> stack(250000);
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value)
	{
		if (comm == 'i')
			stack.push(value);
		else
			stack.pop();
	}		
}	

void RunQueueAr (char *filename)
{
	Queue<int> queue(250000);
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value)
	{
		if (comm == 'i')
			queue.enqueue(value);
		else
			queue.dequeue();
	}		
}	

void RunSkipList (char *filename)
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
