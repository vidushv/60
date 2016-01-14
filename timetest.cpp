#include <iostream>
#include <fstream>
#include <vector>
#include "CPUTimer.h"
#include "QueueAr.h"
#include "StackAr.h"
#include "StackLi.h"
#include "SkipList.h"
#include "CursorList.h"
#include "LinkedList.h"
vector<CursorNode <int> > cursorSpace(500000);

using namespace std;

void RunList(char *);
void RunCursorList (char * filename);
void RunStackAr (char *filename);
void RunStackLi (char *filename);
void RunQueueAr (char *filename);
void RunSkipList (char *filename);
int getChoice();

int main (int argc, char** argv)
{	

	CPUTimer ct;
	int choice;
	char filename[79];
	cout << "Filename: ";
	cin >> filename;

	do 
	{
		choice = getChoice();
		ct.reset();
		switch (choice) //Switch statement based on user's choice
		{
			case 1: RunList(filename); break;
			case 2: RunCursorList(filename); break;
			case 3: RunStackAr(filename); break;
			case 4: RunStackLi(filename); break;
			case 5: RunQueueAr(filename); break;
			case 6: RunSkipList(filename); break;
		} // end switch

		cout << "CPU time: " << ct.cur_CPUTime() << endl;
	
	} while (choice > 0);	//end doWhile


	return 0;

}//main

int getChoice()
{
  
	int userChoice;
	cout << endl;
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
}//getChoice

void RunList (char *filename)
{
	List<int> list;
	ListItr<int> listItr = list.zeroth();
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value) //While values are being read in.
	{
		if (comm == 'i') //if the file says to insert.
			list.insert(value, listItr);
		else //othwerise.
			list.remove(value);
	}//end while
}//RunList

void RunCursorList (char * filename)
{
	CursorList<int> list(cursorSpace);
	CursorListItr<int> listItr = list.zeroth();
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value) //While values are being read in.
	{
		if (comm == 'i') //if the file says to insert.
			list.insert(value, listItr);
		else //otherwise.
			list.remove(value);
	}//end while.
}//RunCursorList	

void RunStackAr (char *filename)
{
	StackAr<int> stack(500000);
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value) //while values are being read in.
	{
		if (comm == 'i') //if the file says to read in.
			stack.push(value);
		else //otherwise.
			stack.pop();
	}		
}//RunStackAr

void RunStackLi (char *filename)
{
	StackLi<int> stack;
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value) //while values are being read in.
	{
		if (comm == 'i') //if the file says to read in.
			stack.push(value);
		else //otherwise.
			stack.pop();
	}		
}//RunStackLi

void RunQueueAr (char *filename)
{
	Queue<int> queue(500000);
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value) //while values are being read in.
	{
		if (comm == 'i') //if the file says to insert.
			queue.enqueue(value);
		else //othwerise.
			queue.dequeue();
	}		
}//RunQueueAr

void RunSkipList (char *filename)
{
	SkipList<int> list(-1, 500000);
	ifstream inf(filename);
	char comm, s[512];
	int value;
	inf.getline(s, 512);
	while (inf >> comm >> value)//while values are being read in.
	{
		if (comm == 'i') //if the file says to insert.
			list.insert(value);
		else //othwerise.
			list.deleteNode(value);
	}		
}//RunSkipList