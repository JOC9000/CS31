#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "Defendant: ";
	string defendant;
	getline(cin, defendant);

	cout << "Amount paid (in thousands): ";
	double amount;
	cin >> amount;

	cout << "Fake Athlete? (y/n): ";
	string fakeAthlete;
	cin >> fakeAthlete;

	cout << "---" << endl;

	double payAmt = 20;

	if (amount <= 40)		//Start of Calculation instances
	{
		payAmt = 66 * amount / 100 + 20;
	}

	if(amount > 40 && amount <= 250 && fakeAthlete == "n")
	{
		payAmt = (26.4) + ((amount - 40)/10) + 20;
	}

	if (amount > 40 && amount <= 250 && fakeAthlete == "y")
	{
		payAmt = (26.4) + (22*(amount - 40))/100 + 20;
	}

	if (amount > 250 && fakeAthlete == "n")
	{
		payAmt = (26.4) + (21) + ((14 * (amount - 250))/ 100) + 20;
	}

	if (amount > 250 && fakeAthlete == "y")
	{
		payAmt = (26.4) + (46.2) + ((14*(amount - 250))/ 100) + 20;
	}

	cout.setf(ios::fixed);
	cout.precision(1);

	if (defendant == "")		//Check for input errors
	{
		cout << "You must enter a defendant name." << endl;
		return 0;
	}

	if (amount < 0)
	{
		cout << "The amount paid must not be negative."<<endl;
		return 0;
	}

	if (fakeAthlete != "y" && fakeAthlete != "n")
	{
		cout << "You must enter y or n." << endl;
		return 0;
	}

	cout << "The suggested fine for " << defendant << " is $" << payAmt << " thousand."<<endl;

}//end of main
