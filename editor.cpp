#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#include "linelist.h"

void OpenFile (ifstream& infile, int argc, char *argv[]);
void BuildList (ifstream& infile, LineList& L);
void StartUp(int argc, char *argv[], LineList& L);
void FinishUp (char *argv[], LineList& L);
void GetCommand (LineList& L, char& command);
void Insert (LineList& L);

int main(int argc, char *argv[])
{
	LineList L;	char command;

	StartUp (argc, argv, L);

	do
	{
		GetCommand (L, command);

		switch(command)
		{
			case 'L' :
			 L.printList();  break;
			case 'I' :
			 Insert(L);	break;
			case 'D' :
			 L.deleteLine(); break;
			case 'N' :
			 L.moveNextLine(); break;
			case 'P' :
			 L.movePrevLine(); break; 
			case 'A' :
			 cout << (L.getCurrLineNum()) << endl;
		}
			
	} while (command != 'E');

	FinishUp (argv, L);
	return 0;
}

void Insert (LineList& L)
{
	int lineNum = L.getCurrLineNum()+1;
	string buffer;
	
	if (L.getCurrLineNum() > L.getLength())
		lineNum--;

	cout << lineNum << "> ";
	getline (cin, buffer);
	L.insertLine(buffer);
}
	
void GetCommand (LineList& L, char& command)
{
	cout << L.getCurrLineNum() << "> ";
	cin >> command;	

	cin.ignore (80, '\n');
}
	
void StartUp(int argc, char *argv[], LineList& L)
{
	ifstream infile;

        OpenFile (infile, argc, argv);
        BuildList (infile, L);
        L.printList();
	L.goToBottom();
}

void FinishUp (char *argv[], LineList& L)
{
	ofstream outfile;
	string filename = argv[1];

	outfile.open(filename.c_str());
	L.goToTop();

	for (int i = 1;  i <= L.getLength();  i++)
	{
		outfile << L.getCurrLine() << endl;
		L.moveNextLine();
	}
	outfile.close();
}

void OpenFile (ifstream& infile, int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "Error -- No Filename Entered!" << endl;
		exit(1);
	}

	string filename = argv[1];
	infile.open(filename.c_str());
} 
	
void BuildList (ifstream& infile, LineList& L)
{
	if (infile)
	{
		string buffer;

		getline (infile, buffer);
		while (infile)
		{
			L.insertLine(buffer);
			getline (infile, buffer);
		}
		infile.close();
	}
}
