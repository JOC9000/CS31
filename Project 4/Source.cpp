#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

int appendToAll(string a[], int n, string value)
{
	if (n < 0)
		return -1;

	for (int arrayPos = 0; arrayPos < n; arrayPos++)//goes through and adds value to each string
		a[arrayPos] += value;

	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0)
		return -1;

	for (int arrayPos = 0; arrayPos < n; arrayPos++)//checks to see if any string in the array is equal to target, and if it does returns the position of that array
	{
		if (a[arrayPos] == target)
			return arrayPos;
	}

	return -1;
}

int positionOfMax(const string a[], int n)
{
	int greatestPos = 0;//position of the greatest string
	string currentGreatest;//establish a Greatest empty string
	if (n <= 0)
		return -1;

	for(int arrayPos = 0; arrayPos < n; arrayPos++)//checks to see in order if strings are greater than the current greatest
	{
		if (a[arrayPos] > currentGreatest)//if greater, sets the currentGreatest to that string and updates the greatestPos, which will be returned to show the position of the greatest string
		{
			currentGreatest = a[arrayPos];
			greatestPos = arrayPos;
		}
	}

	return greatestPos;
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos < 0 || n < pos)
		return -1;

	if (n == 0)
		return pos;
	
	string temp = a[pos];//keeps value of string at position pos, for use later
	a[pos] = a[pos + 1];//swap string at position pos to the right

	for (int arrayPos = pos+1; arrayPos < (n-1); arrayPos++)//swaps string until it reaches last string in array
		a[arrayPos] = a[arrayPos + 1];

	a[n-1] = temp;//last relevant string in array set to temp, which stored value of string at position pos

	return pos;
}

int countRuns(const string a[], int n)
{
	int runCount = 1;//initializes runCount as 1, as a singular string will count as a run of 1

	if (n < 0)
		return -1;

	if (n == 0)
		return 0;

	for (int arrayPos = 1; arrayPos < n; arrayPos++)//start at the second string of array, as 1st string was accounted for in initialization
	{
		if (a[arrayPos] != a[arrayPos - 1])//increases runCount if the string at position pos is not equal to the string before it, shows it is a different string
			runCount++;
	}

	return runCount;
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;

	if (n <= 1)
		return n;

	for (int arrayPos = 0; arrayPos < n/2; arrayPos++)//swaps the strings up to the halfway point, as that is all that is needed
	{
		swap(a[arrayPos], a[n - arrayPos-1]);
	}

	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	int lesser = min(n1, n2);//stores value of the smaller array size to be used

	for (int arrayPos = 0; arrayPos < lesser; arrayPos++)//goes through to check where the arrays are not equal
	{
		if (a1[arrayPos] != a2[arrayPos])
			return arrayPos;
	}

	return lesser;//if they are completely equal, returns a default value
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	int count = 0;//used to count how many elements of a2 are present in a2 in order

	if (n1 < 0 || n2 < 0 || n1 < n2)
		return - 1;

	if (n2 == 0)
		return 0;

	for (int arrayPos = 0; arrayPos < n1; arrayPos++)
	{
		for(int a = 0; a < n2; a++)
		{
			if (arrayPos + a < n1 && a1[arrayPos + a] == a2[a])//if element in a2 is equal to a1 in order increase count
				count++;
			else
				break;

			if (count == n2)//if count is equal to n2, a2 is a subsequence of a1, so return value where subsequence starts
				return arrayPos;
		}

		count = 0;
	}

	return -1;//if not a subsequence return a failure
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	for (int arrayPos = 0; arrayPos < n1; arrayPos++)
	{
		for (int arrayPos1 = 0; arrayPos1 < n2; arrayPos1++)//two for loops to go through both strings to check equivalence
		{
			if (a1[arrayPos] == a2[arrayPos1])//if equivalent, send position of equivalent string in a1
				return arrayPos;
		}
	}

	return -1;//if none equivalent return default error
}

int separate(string a[], int n, string seperator)
{
	if (n < 0)
		return -1;

	int count1 = 1, count2 = 0;//initializatoin of count values which help with logic

	for (int arrayPos = 0; arrayPos < n; arrayPos++)
	{
		if (a[arrayPos] > seperator)
		{
			for (int ax = arrayPos + 1; ax < n; ax++)//counts how many strings near the end are also greater than seperator
			{
				if (a[n - count1] > seperator)
					count1++;
				else
					break;
			}
			if((n-count1) > 0)//makes sure the string to be swapped has a valid value before swapping with the last string that is not greater than seperator
			swap(a[arrayPos], a[n - count1]);
		}
		count1 = 1;
	}

	for (int arrayPos = 0; arrayPos < n; arrayPos++)
	{
		if (a[arrayPos] < seperator)
		{
			for (int ax = 0; ax < n; ax++)//counts how many strings near the beginning of arrray are also lesser than seperator
			{
				if (a[count2] < seperator)
					count2++;
				else
					break;
			}
			if(count2 < n)//makes sure the string to be swapped has a valid value before swapping with the first string that is not lesser than seperator
			swap(a[arrayPos], a[count2]);
		}
		count2 = 0;
	}

	for(int arrayPos = 0; arrayPos < n; arrayPos++)//goes through to check whih is the earlies string that is not less than seperator
	{
		if (a[arrayPos] >= seperator)
			return arrayPos;//then returns that value
	}

	return n;//default value to return if no strings in the array are greater than or equal to seperator
}
int main ()
{

}