#include <iostream>
#include <string>
using namespace std;

class Event
{
public:
	Event(string param1)
	{
		m_name = param1;
	}

	virtual string name() const = 0;
	virtual string need() const = 0;
	virtual bool isSport()  const = 0;
	virtual ~Event() {};
private:
	string m_name;
};

class BasketballGame : public Event
{
public:
	BasketballGame(string param): Event(param)
	{
		m_name = param;
	}

	virtual ~BasketballGame()
	{
		cout << "Destroying the " << m_name << " basketball game" << endl;
	}

	virtual string name() const
	{
		return m_name;
	}

	virtual string need() const 
	{
		return "hoops";
	}

	virtual bool isSport() const
	{
		return true;
	}

private:
	string m_name;
};

class Concert : public Event
{
public:
	Concert(string param, string param2) : Event(param)
	{
		m_name = param;
		m_genre = param2;
	}

	virtual ~Concert()
	{
		cout << "Destroying the " << m_name << " " << m_genre<< " concert" << endl;
	}

	virtual string name() const
	{
		return m_name;
	}

	virtual string need() const
	{
		return "a stage";
	}

	virtual bool isSport() const
	{
		return false;
	}

private:
	string m_name;
	string m_genre;
};

class HockeyGame : public Event
{
public:
	HockeyGame(string param) : Event(param)
	{
		m_name = param;
	}

	virtual ~HockeyGame()
	{
		cout << "Destroying the " << m_name << " hockey game"<< endl;
	}

	virtual string name() const
	{
		return m_name;
	}

	virtual string need() const
	{
		return "ice";
	}

	virtual bool isSport() const
	{
		return true;
	}

private:
	string m_name;
};

void display(const Event* e)
{
	cout << e->name() << ": ";
	if (e->isSport())
		cout << "(sport) ";
	cout << "needs " << e->need() << endl;
}

int main()
{
	Event* events[4];
	events[0] = new BasketballGame("Lakers vs. Suns");
	// Concerts have a name and a genre.
	events[1] = new Concert("Banda MS", "banda");
	events[2] = new Concert("KISS", "hard rock");
	events[3] = new HockeyGame("Kings vs. Flames");

	cout << "Here are the events." << endl;
	for (int k = 0; k < 4; k++)
		display(events[k]);

	// Clean up the events before exiting
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete events[k];
}