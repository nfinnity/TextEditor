
#include "linelist.h"

LineList::LineList()
{
	LineNode *line = new LineNode;
	LineNode *line2 = new LineNode;

	line -> info = topMessage;
	currLine = line;
	currLineNum = 1;
	length = 0;
	line2 -> info = bottomMessage;
	currLine -> back = NULL;
	currLine -> next = line2;
	line2 -> back = line;
	line2 -> next = NULL;
}

void LineList::goToTop() 
{
	// Post : Advances currLine to line 1
	//Checks to see if it's at the top already or if the spot is null.
	if ((currLine -> info == topMessage) || (currLine -> back == NULL))
	{}
	//Continues calling movePrevLine() until it reaches the spot before the top.
	else
	{
		while (currLine -> back -> info != topMessage)
			movePrevLine();
	}
}

void LineList::goToBottom() 
{
	// Post : Advances currLine to last line
	//Checks to see if it's at the bottom already or if the spot is null.
	if ((currLine -> info == bottomMessage) || (currLine -> next == NULL))
	{}
	//Continues calling moveNextLine() until it reaches the spot before the bottom.
	else
	{
		while (currLine -> next -> info != bottomMessage)
		{
			moveNextLine();
		}
	}
}

void LineList::insertLine(string newLine)
{
	// post : newLine has been inserted after the current line

	LineNode *line = new LineNode;
	
	line -> info = newLine;
	line -> back = currLine;
	line -> next = currLine -> next;
	currLine -> next -> back = currLine;
	currLine -> next = line;
	currLine = currLine -> next;
	length++;
	if (length != 1)
		currLineNum++;
}

void LineList::deleteLine()
{
	// post : deletes the current line leaving currentLine
	//	  pointing to line following

	//If it's not at the top, the bottom, or at a null spot, then delete the line.
	if ((currLine -> info != topMessage) && (currLine -> info != bottomMessage) && (currLine != NULL))
	{
		currLine -> back -> next = currLine -> next;
		currLine -> next -> back = currLine -> back;
		delete currLine;
		currLine = currLine -> back;
		if (currLineNum > 1)
			currLineNum--;
		length--;		
	}
	else
		cout << "NOTHING TO DELETE" << endl;
}

void LineList::printList() 
{
	int lineNum = 1;

	LineNode *mark = currLine;
	int markNum = currLineNum;

	goToTop();

	//List is not empty, so print text lines out.
	if (length > 0)
	{
		LineNode *line = currLine;

		while (line -> info != bottomMessage)
		{
			cout << lineNum << "> " << line -> info << endl;
			line = line -> next;
			lineNum++;
		}
	}

	currLine = mark;
	currLineNum = markNum;
}

string LineList::getCurrLine() const
{
	return (currLine -> info);
}

void LineList::moveNextLine()
{
	// Post : Advances currLine (unless already at last line)
	if ((currLine -> next -> info != bottomMessage) && (currLine -> next != NULL))
	{
		currLine = currLine -> next;
		currLineNum++;
	}
}

void LineList::movePrevLine()
{
	// Post : Advances currLine (unless already at last line)
	if ((currLine -> back -> info != topMessage) && (currLine -> back != NULL) && (currLine != NULL))
	{
		currLine = currLine -> back;
		currLineNum--;
	}
}

int LineList::getCurrLineNum() const
{
	return currLineNum;
}

int LineList::getLength() const
{
	return length;
}
