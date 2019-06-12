#include <iostream>
#include <vector>

using namespace std;

// Before:
/*
The architect has done an admirable job of decoupling the client from Stooge concrete derived 
classes, and, exercising polymorphism. But three remains coupling where instances are actually 
created if we design an "extra level of indirection" (a "factory method") and have clients use 
it (instead of "new"), then the last bit of coupling goes away. The "factory method"(aka "virtual constructor")
can be defined in the Stooge base class, in a separate "factory" class. Note that main() is no longer
dependent on Stooge derived classes.
*/

/*
class Stooge
{
public:
	virtual void slap_stick() = 0;
};

class Larry : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Larry: poke eyes\n";
	}
};

class Moe : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Moe: slap head\n";
	}
};

class Curly : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Curly: suffer abuse\n";
	}
};

int main()
{
	vector<Stooge *> roles;
	int choice;

	while (true)
	{
		cout << "Larry(1) Moe(2) Curly(3) Go(0):";
		cin >> choice;
		if (choice == 0)
			break;
		else if (choice == 1)
		{
			roles.push_back(new Larry);
		}
		else if (choice == 2)
		{
			roles.push_back(new Moe);
		}
		else
		{
			roles.push_back(new Curly);
		}
	}

	for (int i = 0; i < roles.size(); ++i)
	{
		roles[i]->slap_stick();
	}
	for (int i = 0; i < roles.size(); ++i)
	{
		delete roles[i];
	}
	getchar();
	getchar();
}
*/

/*
A factory method is a static method of a class that returns an object of that class's type.
But unlike a constructor, the actual object it returns might be an instance of a subclass.
Another advantage of a factory method is that it can return existing instances multiple times.
*/

/*
class Stooge
{
public:
	// Factory Method
	static Stooge *make_stooge(int choice);
	virtual void slap_stick() = 0;
};

int main()
{
	vector<Stooge*> roles;
	int choice;
	while(true)
	{
		cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
		cin >> choice;
		if (choice == 0)
			break;
		roles.push_back(Stooge::make_stooge(choice));
	}
	for(int i = 0; i < roles.size(); ++i)
	{
		roles[i]->slap_stick();
	}
	for (int i = 0; i < roles.size(); ++i)
	{
		delete roles[i];
	}
	getchar();
	getchar();
}

class Larry : public Stooge
{
public: 
	void slap_stick()
	{
		cout << "Larry: poke eyes\n";
	}
};

class Moe : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Moe: slap head\n";
	}
};

class Curly : public Stooge
{
public:
	void slap_stick()
	{
		cout << "Curly: suffer abuse\n";
	}
};

Stooge* Stooge::make_stooge(int choice)
{
	if (choice == 1)
	{
		return new Larry;
	}
	else if (choice == 2)
	{
		return new Moe;
	}
	else
	{
		return new Curly;
	}
}
*/

// Another Factory Method C++ source code example

/*
Discussion. Frameworks are applications(or subsystems) with "holes" in them. Each framework specifies the infrastructure,
superstructure, and flow of control for its "domain", and the client of the framework may:exercise 
framework's default behavior "as is", extend selected pieces of the framework, or replace selected 
pieces of the framework, or replace selected pieces.

The Factory Method pattern addresses the notion of "creation" in the context of frameworks. In this 
example, the framework knows WHEN a new document should be created, not WHAT kind of Document to create.
The "placeholder" Appliction::CreateDocument() has been declared by the framework, and the client is 
expected to "fill in the blank" for his/her specific document(s).Then, when the client asks for Application::NewDocument(),
the framework will subsequently call the client's MyApplication::CreateDocument().
*/

/* Abstract base class declared by framework */

class Document
{
public:
	Document(char *fn)
	{
		strcpy(name, fn);
	}

	virtual void Open() = 0;
	virtual void Close() = 0;

	char *GetName()
	{
		return name;
	}

private:
	char name[20];
};


/* Concrete derived class defined by client */
class MyDocument : public Document
{
public:
	MyDocument(char *fn) : Document(fn){}

	void Open()
	{
		cout << "  MyDocument: Open()" << endl;
	}
	void Close()
	{
		cout << "  MyDocument: Close()" << endl;
	}
};

/* Framework declaration */
class Application
{
public:
	Application() : _index(0)
	{
		cout << "Application: ctor" << endl;
	}

	/* The client will call this "entry point" of the framework */
	void NewDocument(char *name)
	{
		cout << "Application: NewDocument()" << endl;
		/* Framework calls the "hole" reserved for client customlization */
		_docs[_index] = CreateDocument(name);
		_docs[_index++]->Open();
	}
	void OpenDocument(){}
	void ReportDocs();
	/* Framework declares a "hole" for the client to customize*/
	virtual Document *CreateDocument(char*) = 0;

private:
	int _index;
	/* Framework uses Document's base class */
	Document *_docs[10];
};

void Application::ReportDocs()
{
	cout << "Application: ReportDocs()" << endl;
	for (unsigned int i = 0; i < _index; ++i)
	{
		cout << "   " << _docs[i]->GetName() << endl;
	}
}

/* Customization of framework defined by client */
class MyApplication : public Application
{
public:
	MyApplication()
	{
		cout << "MyApplication: ctor" << endl;
	}

	/* Client defines framework's "hole" */
	Document *CreateDocument(char *fn)
	{
		cout << "  MyApplication: CreateDocument()" << endl;
		return new MyDocument(fn);
	}
};

int main()
{
	/* Client's customization of the Framework */
	MyApplication myApp;

	myApp.NewDocument("foo");
	myApp.NewDocument("bar");
	myApp.ReportDocs();

	getchar();
}