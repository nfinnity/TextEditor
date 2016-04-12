
#include <string>
#include <iostream>
using namespace std;

const string topMessage = " - - - Top of file - - - ";
const string bottomMessage = " - - - Bottom of file - - - ";

struct LineNode;

class LineList
{
public:
	LineList();  
  	void goToTop();
  	void goToBottom();
  	void insertLine (string newLine);
	void deleteLine ();
	void printList();
	void moveNextLine();
	void movePrevLine();
	int getCurrLineNum() const;
	int getLength() const;
	string getCurrLine() const;

private:
	LineNode*	currLine;
	int currLineNum;
	int length;
};

struct LineNode
{
	string info;
	LineNode* next;
	LineNode* back;
	
};
