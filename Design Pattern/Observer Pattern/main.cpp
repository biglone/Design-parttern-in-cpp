#include <iostream>
#include <vector>


using namespace std;

// before:
// The number and type of "user interface" (or dependent) objects is hard-wired in the
// Subject Class. The user has no abffect this configuration.

/*
class DivObserver
{
	int m_div;
public:
	DivObserver(int div)
	{
		m_div = div;
	}

	void update(int val)
	{
		cout << val << " div " << m_div << " is " << val / m_div << '\n';
	}
};

class ModObserver
{
	int m_mod;
public:
	ModObserver(int mod)
	{
		m_mod = mod;
	}

	void update(int val)
	{
		cout << val << " mod " << m_mod << " is " << val % m_mod << '\n';
	}
};

class Subject
{
	int m_value;
	DivObserver m_div_obj;
	ModObserver m_mod_obj;
public:
	Subject(): m_div_obj(4), m_mod_obj(3){}
	void set_value(int value)
	{
		m_value = value;
		notify();
	}
	void notify()
	{
		m_div_obj.update(m_value);
		m_mod_obj.update(m_value);
	}
};


int main()
{
	Subject subj;
	subj.set_value(14);
	getchar();
}

*/

// After: 
// The Subject class is now decoupled from the number and type of Observer objects.
// The client has asked for two DivObserver delegates(each configured differently), and
// one ModObserver delegate.

// class Observer
// {
// public:
// 	virtual void update(int value) = 0;
// };
// 
// class Subject
// {
// 	int m_value;
// 	vector<Observer*> m_views;
// 
// public:
// 	void attach(Observer *obs)
// 	{
// 		m_views.push_back(obs);
// 	}
// 	
// 	void set_val(int value)
// 	{
// 		m_value = value;
// 		notify();
// 	}
// 	
// 	void notify()
// 	{
// 		for (int i = 0; i < m_views.size(); ++i)
// 		{
// 			m_views[i]->update(m_value);
// 		}
// 	}
// };
// 
// class DivObserver : public Observer
// {
// 	int m_div;
// public:
// 	DivObserver(Subject *model, int div)
// 	{
// 		model->attach(this);
// 		m_div = div;
// 	}
// 
// 	void update(int v)
// 	{
// 		cout << v << " div " << m_div << " is " << v / m_div << '\n';
// 	}
// };
// 
// class ModObserver : public Observer
// {
// 	int m_mod;
// public:
// 	ModObserver(Subject *model, int mod)
// 	{
// 		model->attach(this);
// 		m_mod = mod;
// 	}
// 
// 	void update(int v)
// 	{
// 		cout << v << " mod " << m_mod << " is " << v % m_mod << '\n';
// 	}
// };
// 
// 
// int main()
// {
// 	Subject subj;
// 	DivObserver divObs1(&subj, 4);
// 	DivObserver divObs2(&subj, 3);
// 	ModObserver modObs3(&subj, 3);
// 	subj.set_val(14);
// 	getchar();
// }



// SensorSystem is the "subject". Lighting, Gates, and Surveillance are the "views".
// The Subject is only coupled to the "abstraction" of AlarmListener.
// An Object's class defines how the object is implemented. In contrast, an object's type
// only refers to its interface. Class inheritance defines an object's implementation terms
// of another object's implementation. Type inheritance describes when an object can be used
// in place of another.

class AlarmListener
{
public:
	virtual void alarm() = 0;
};

class SensorSystem
{
	vector <AlarmListener *> listeners;
public:
	void attach(AlarmListener *al)
	{
		listeners.push_back(al);
	}
	void soundTheAlarm()
	{
		for (int i = 0; i < listeners.size(); ++i)
		{
			listeners[i]->alarm();
		}
	}
};

class Lighting : public AlarmListener
{
public:
	void alarm()
	{
		cout << "lights up" << '\n';
	}
};

class Gates : public AlarmListener
{
public:
	void alarm()
	{
		cout << "gates close" << '\n';
	}
};

class CheckList
{
	virtual void localize()
	{
		cout << "  establish a perimeter" << '\n';
	}
	
	virtual void isolate()
	{
		cout << "  isolate the grid" << '\n';
	}

	virtual void identify()
	{
		cout << "  identify the source" << '\n';
	}

public:
	void byTheNumbers()
	{
		// Template Method design pattern
		localize();
		isolate();
		identify();
	}
};

class Surveillance : public CheckList, public AlarmListener
{
	void isolate()
	{
		cout << "  train the cameras" << '\n';
	}
public:
	void alarm()
	{
		cout << "Surveillance - by the numbers:" << "\n";
		byTheNumbers();
	}
};

int main()
{
	SensorSystem ss;
	ss.attach(new Gates());
	ss.attach(new Lighting());
	ss.attach(new Surveillance());
	ss.soundTheAlarm(); // why call child's 'isolate()' ?
	getchar();
}
