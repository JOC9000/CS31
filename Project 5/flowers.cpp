#pragma warning(disable:6262)
#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <utility>
#include <string>
using namespace std;

int countFlowers(char wordGuess[], const char words[][7], int wordnum, bool counted[], bool counted1[])//counts flowers and changes usage arrays to true when matched
{
	int count = 0;

	for (int l = 0; l < strlen(words[wordnum]); l++)
	{
		if (l == strlen(wordGuess))
			return count;

		if (words[wordnum][l] == wordGuess[l])
		{
			count++;
			counted[l] = true;//used to see if particular poin in word has been used for flower before
			counted1[l] = true;
		}
	}

	return count;
}

int countBees(char wordGuess[], const char words[][7], int wordnum, bool counted[], bool counted1[])//counts bees and sets elements of relevant count arrays to true when used 
{
	int count = 0;


	for (int l = 0; l < strlen(wordGuess); l++)
	{
		for (int k = 0; k < strlen(words[wordnum]); k++)
		{
			if (wordGuess[l] == words[wordnum][k] && k != l && counted[l] == false && counted1[k] == false)//if characters match and neither has been used before
			{
				count++;
				counted[l] = true;
				counted1[k] = true;
				break;
			}
		}

	}

	return count;
}

int playOneRound(const char words[][7], int nWords, int wordnum)
{
	bool count[6], count1[6];//initialize, used to check if elements of trial word and correct word have been used

	if (nWords <= 0 || wordnum < 0)
		return -1;

	int tries = 0;

	for (int p = 0; p < 1; p--)//continues to run until equivalence checker causes funciton to return correct amount of tries 
	{
		bool isMatch = false;
		char wordGuess[10000];
		cout << "Trial word: ";
		cin.getline(wordGuess, 1000);


			if (strlen(wordGuess) < 4 || strlen(wordGuess) > 6 || 0 < (strlen(wordGuess) > 0 && !islower(wordGuess[0])) || (strlen(wordGuess) > 1 && !islower(wordGuess[1])) || (strlen(wordGuess) > 2 && !islower(wordGuess[2])) || (strlen(wordGuess) > 3 && !islower(wordGuess[3])) || (strlen(wordGuess) > 4 && !islower(wordGuess[4])) || (strlen(wordGuess) > 5 && !islower(wordGuess[5])))
			{
				cout << "The trial word must be a word of 4 to 6 lower case letters" << endl;
				continue;
			}
		

		for (int i = 0; i < nWords; i++)// checks if trial word is within the wordlist
		{
			if (strcmp(wordGuess, words[i]) == 0)
			{
				isMatch = true;
			}
		}

		if (isMatch == false)
		{
			cout << "I don't know that word."<<endl;
				continue;
		}

		tries++;

		if (strcmp(wordGuess, words[wordnum]) == 0)
			return tries;

		for (int a = 0; a < 6; a++)//initializes count arrays each loop so that earlier loops do not affect proper flowers and bees of later ones
		{
			count[a] = false;
			count1[a] = false;
		}

		cout<<"Flowers: "<<countFlowers(wordGuess, words, wordnum, count, count1);
		cout << ", Bees: " << countBees(wordGuess, words, wordnum, count, count1);
		cout << endl;
	}

	return tries;
}

int main ()
{

	int numRounds;
	int const MAXWORDS = 9000;
	char wordList [MAXWORDS][7];
	char tocompare[7] = "";
	const char WORDFILENAME[] = "C:/Users/user/Downloads/words.txt";

	for (int a = 0; a < 9000; a++)//initializes all elements in C string array to empty strings. Necessary? Probably not. 
	{
		strcpy(wordList[a], "");
	}

	int nWords = getWords(wordList, MAXWORDS, WORDFILENAME);
	int points = 0;
	int minPoints;//min and max used to display current minimum and maximums
	int maxPoints;


	if(nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game.";
		return 0;
	}

	cout << "How many rounds do you want to play? ";
	cin >> numRounds;

	if (numRounds < 1)
	{
		cout << "The number of rounds must be positive." << endl;
		return 0;
	}

	cin.ignore(1000, '\n');

	for (int i = 0; i < numRounds; i++)
	{
		int currentpoints = 0;//initialize points from round, used for average 
		cout << endl << "Round " << i+1<<endl;
		int wordnum = randInt(0, nWords-1);
		cout << "The mystery word is " << strlen(wordList[wordnum])<<" letters long."<<endl;
		currentpoints = playOneRound(wordList, nWords, wordnum);

		if (currentpoints == 1)//Displays correct success message based on tries. 
			cout << "You got it in 1 try." << endl;

		else
			cout << "You got it in " << currentpoints << " tries." << endl;

		points = currentpoints + points;//cumaltive points 

		if (i == 0)//sets min and max to current point if in first round
		{
			minPoints = points;
			maxPoints = points;
		}

		else//sets min and max to current points if is less than or greter than, respectibly
		{
			minPoints = min(minPoints, currentpoints);
			maxPoints = max(maxPoints, currentpoints);
		}

		double yeet = points;//puts values into double so that average comes out as proper double
		double yote = i;
		double avg = yeet / (yote + 1);
		cout.setf(ios::fixed);      
		cout.precision(2);
		cout << "Average: " << avg << ", minimum: " << minPoints << ", maximum: " << maxPoints << endl;
	}//end of for loop
}