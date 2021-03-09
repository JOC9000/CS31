#include "grid.h"
#include <cctype>
#include <iostream>
#include <string>
using namespace std;
const int HORIZ = 0;
const int VERT = 1;
const int FG = 0;
const int BG = 1;

int convertInt(string toconvert)//Turns a digit substring into the corresponding integer
{
	int size = toconvert.size();
	int finishedInt;

	if (size == 1)
	{
			finishedInt = toconvert[0] - '0';
	}

	else if (toconvert[0] == '-')
	{
		if (size == 2)
			finishedInt = -1 * (toconvert[size - 1] - '0');

		if (size == 3)
			finishedInt = -1 * ((toconvert[size - 1] - '0') + (10 * (toconvert[size - 2] - '0')));
	}

	else
			finishedInt = (toconvert[size - 1] - '0') + (10 * (toconvert[size - 2] - '0'));

	return finishedInt;
}

int detSize(string commandString, int currentPos)// determines the size of an integer substring after a 'H' or 'V'
{
	int count = 0;

	for (string::size_type k = currentPos; k < commandString.size(); k++)
	{
		if ((commandString[k] == '-' && count == 0) || isdigit(commandString[k]))
			count++;

		else
			break;
	}

	return count;
}
bool plottableLine(int r, int c, int distance, int dir)//checks to make sure a line is plottable by making sure the begining and endpoint are within the grid
{
	if (r <= 20 && r >= 1 && c <= 30 && c >= 1)
	{
		if (dir == VERT && r + distance <= 20 && r + distance >= 1)
			return true;

		if (dir == HORIZ && c + distance <= 30 && c + distance >= 1)
			return true;

		else
		return false;
	}

	else
	return false;
}

void plotHorizontalLine(int r, int c, int distance, char ch)//plots a horizontal line
{
	for (int n = 0; n <= distance; n++)
	{
			setChar(r, c + n, ch);
	}
}

void plotVerticalLine(int r, int c, int distance, char ch)//plots a foreground vertical line
{
	for (int n = 0; n <= distance; n++)
	{
			setChar(r + n, c, ch);
	}
}

void plotRectangle(int r, int c, int height, int width, char ch)//calls to toherfunctions necessary to plot a hwole rectangle
{
	plotHorizontalLine(r, c, width, ch);
	plotVerticalLine(r, c, height, ch);
	plotVerticalLine(r, c+width, height, ch);
	plotHorizontalLine(r+height, c, width, ch);
}

void plotHorizontalBGLine(int r, int c, int distance, char ch)//plots a horizontal line in the background
{
	for (int n = 0; n <= distance; n++)
	{
		if (getChar(r, c + n) == ' ')
			setChar(r, c + n, ch);
	}
}

void plotVerticalBGLine(int r, int c, int distance, char ch)//plots a vertical line in the background
{
	for (int n = 0; n <= distance; n++)
	{
		if (r + n <= 20 && r + n >= 1 && c <= 30 && c >= 1 && getChar(r+n, c) == ' ')
			setChar(r + n, c, ch);
	}
}

bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)//calls to correct necesarry funtion to plot any given line
{
	if ((dir == VERT || dir == HORIZ) && (fgbg == BG || fgbg == FG) && plottableLine(r, c, distance, dir) && isprint(plotChar))
	{
		if (fgbg == FG)
		{
			if (dir == HORIZ)
			{
				if (distance < 0)
					plotHorizontalLine(r, c + distance, 0-distance, plotChar);
				else
					plotHorizontalLine(r, c, distance, plotChar);
			}
			else
			{
				if (distance < 0)
					plotVerticalLine(r + distance, c, 0-distance, plotChar);
				else
					plotVerticalLine(r, c, distance, plotChar);
			}
		}

		else
		{
			if (dir == HORIZ)
			{
				if (distance < 0)
					plotHorizontalBGLine(r, c + distance, 0-distance, plotChar);
				else
					plotHorizontalBGLine(r, c, distance, plotChar);
			}

			else
			{
				if (distance < 0)
					plotVerticalBGLine(r + distance, c, 0-distance, plotChar);
				else
					plotVerticalBGLine(r, c, distance, plotChar);
			}
		}

		return true;
	}

	else
		return false;
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)//interprets commandString and calls functions necessary to plot lines
{

	int rPos = 1, cPos = 1;
	int digitsize, distance;
	string toInt;
	int size = commandString.size();

	for (int n = 0; n < commandString.size(); n++)
	{
		switch(commandString[n])
		{
		case 'V':
		case 'v':
			n++;

			if (n == size)
				return 1;

			digitsize = detSize(commandString, n);

			if (digitsize == 0 || (digitsize == 1 && commandString[n] == '-') || (digitsize == 3 && commandString[n] != '-'))
			{
				badPos = n;
				return 1;
			}

			if (digitsize > 3)
			{
				n += 3;
				badPos = n;
				return 1;
			}

			toInt = commandString.substr(n, digitsize);

			for (string::size_type l = 1; l < toInt.size(); l++)
			{
				if (toInt[l] == '-')
				{
					n += l;
					badPos = n;
					return 1;
				}
			}

			distance = convertInt(toInt);

			if (plottableLine(rPos, cPos, distance, VERT))
				plotLine(rPos, cPos, distance, VERT, plotChar, mode);

			else
			{
				badPos = n-1;
				if (badPos < 0)
					badPos = 0;
				return 2;
			}

			rPos += distance;
			n += digitsize-1;
			break;

		case 'H': 
		case 'h': //code is mostly repeated from 'V' cases, only differences that are necessary to make it horizontal are made. Could be combined into one function called by either case.
			n++;

			if (n == size)
				return 1;

			digitsize = detSize(commandString, n);

			if (digitsize == 0 || (digitsize == 1 && commandString[n] == '-') || (digitsize == 3 && commandString[n] != '-'))
			{
				badPos = n;
				return 1;
			}

			if (digitsize > 3)
			{
				n += 3;
				badPos = n;
				return 1;
			}

			toInt = commandString.substr(n, digitsize);

			for(string::size_type l= 1; l < toInt.size(); l++)
			{
				if (toInt[l] == '-')
				{
					n += l;
					n = badPos;
					return 1;
				}
			}

			distance = convertInt(toInt);

			if (plottableLine(rPos, cPos, distance, HORIZ))
				plotLine(rPos, cPos, distance, HORIZ, plotChar, mode);

			else
			{
				badPos = n-1;
				if (badPos < 0)
					badPos = 0;
				return 2;
			}

			cPos += distance;
			n += digitsize-1;
			break;

		case 'C':
		case 'c':
			clearGrid();
			rPos = 1;
			cPos = 1;
			plotChar = '*';
			mode = FG;
			break;

		case 'F':
		case 'f':
			n++;

			if (n == commandString.size())
				return 1;

			plotChar = commandString[n];
			mode = FG;
			break;

		case 'B':
		case 'b':
			n++;

			if (n == commandString.size())
				return 1;

			plotChar = commandString[n];
			mode = BG;
			break;

		default:
			badPos = n;
			return 1;
			break;
		}
	}

	return 0;
}

int main()
{
	setSize(20, 30);
	char currentChar = '*';
	int currentMode = FG;
	for (;;)
	{
		cout << "Enter a command string: ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "")
			break;
		int position;
		int status = performCommands(cmd, currentChar, currentMode, position);
		switch (status)
		{
		case 0:
			draw();
			break;
		case 1:
			cout << "Syntax error at position " << position + 1 << endl;
			break;
		case 2:
			cout << "Cannot perform command at position " << position + 1 << endl;
			break;
		default:
			// It should be impossible to get here.
			cerr << "performCommands returned " << status << "!" << endl;
		}
	}
}