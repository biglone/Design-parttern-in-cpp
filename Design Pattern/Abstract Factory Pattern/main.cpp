/*
Trying to maintain portability across multiple "platforms" routinely requires lots of preprocessor
"case" statements. The Factory pattern suggests defining a creation services interface in a Factory
base class, and implementing each "platform" ia a separate Factory derived class.
*/

// Before:
/*
The client creates "product" objects directly, and must embed all possible platform permutations in
nasty looking code.
*/


// #include <iostream>
// #define LINUX
// 
// using namespace std;
// 
// class Widget
// {
// public:
// 	virtual void draw() = 0;
// };
// 
// /************************************************************************/
// /* Concrete product family 1.                                                                     */
// /************************************************************************/
// class LinuxButton : public Widget
// {
// public:
// 	void draw()
// 	{
// 		cout << "LinuxButton\n";
// 	}
// };
// 
// class LinuxMenu : public Widget
// {
// public:
// 	void draw()
// 	{
// 		cout << "LinuxMenu\n";
// 	}
// };
// 
// /************************************************************************/
// /*  Concrete product family 2.                                                                     */
// /************************************************************************/
// class WindowsButton : public Widget
// {
// public:
// 	void draw()
// 	{
// 		cout << "WindowsButton\n";
// 	}
// };
// 
// class WindowsMenu : public Widget
// {
// public:
// 	void draw()
// 	{
// 		cout << "WindowsMenu\n";
// 	}
// };
// 
// /************************************************************************
// * Here's a client, which users concrete products directly.
// * It's code filled up with nasty switch statements
// * which check the product type before its use.
// */
// 
// class Client
// {
// public:
// 	void draw()
// 	{
// #ifdef LINUX
// 		Widget *w = new LinuxButton;
// #else
// 		Widget *w = new WindowsButton;
// #endif
// 		w->draw();
// 		dispaly_window_one();
// 		display_window_two();
// 	}
// 
// 	void dispaly_window_one()
// 	{
// #ifdef LINUX
// 		Widget *w[] = {
// 			new LinuxButton,
// 			new LinuxMenu
// 		};
// #else
// 		Widget *w[] = {
// 			new WindowsButton, 
// 			new WindowsMenu
// 		};
// #endif
// 		w[0]->draw();
// 		w[1]->draw();
// 	}
// 
// 	void display_window_two()
// 	{
// #ifdef LINUX
// 		Widget *w[] = {
// 			new LinuxButton,
// 			new LinuxMenu
// 		};
// #else
// 		Widget *w[] = {
// 			new WindowsButton, 
// 			new WindowsMenu
// 		};
// #endif
// 		w[0]->draw();
// 		w[1]->draw();
// 	}
// };
// 
// int main()
// {
// 	Client *c = new Client();
// 	c->draw();
// 	getchar();
// }

// After:
/*
*	The client receives a platform-specific factory object, witch encapsulates use of "new" operator.
*	Client delegates all creation results to this factory.
*/


// #include <iostream>
// #define LINUX
// 
// using namespace std;
// 
// /**
// * Abstract base product. It should define an interface
// * which will be common to all products. Clients will 
// * work with products through this interface, so it 
// * should be sufficient to use all products.
// */
// 
// class Widget
// {
// public:
// 	virtual void draw() = 0;
// };
// 
// /**
//  * Concrete product family 1.
//  */
// class LinuxButton : public Widget {
//  public:
//   void draw() { cout << "LinuxButton\n"; }
// };
// class LinuxMenu : public Widget {
//  public:
//   void draw() { cout << "LinuxMenu\n"; }
// };
// 
// /**
//  * Concrete product family 2.
//  */
// class WindowsButton : public Widget {
//  public:
//   void draw() { cout << "WindowsButton\n"; }
// };
// class WindowsMenu : public Widget {
//  public:
//   void draw() { cout << "WindowsMenu\n"; }
// };
// 
// /**
// * Abstract factory defines methods to create all 
// * related products.
// */
// 
// class Factory
// {
// public:
// 	virtual Widget *create_button() = 0;
// 	virtual Widget *create_menu() = 0;
// };
// 
// /**
// * Each concrete factory corresponds to one product
// * family. It create all possible products of one kind.
// */
// 
// class LinuxFactory : public Factory
// {
// public:
// 	Widget *create_button()
// 	{
// 		return new LinuxButton;
// 	}
// 	Widget *create_menu()
// 	{
// 		return new LinuxMenu;
// 	}
// };
// 
// /**
// * Concrete factory creates concrete products, but
// * return them as abstract.
// */
// 
// class WindowsFactory : public Factory
// {
// public:
// 	Widget * create_button()
// 	{
// 		return new WindowsButton;
// 	}
// 	Widget *create_menu()
// 	{
// 		return new WindowsMenu;
// 	}
// };
// 
// /**
// * Client receives a factory object from its creator.
// *
// * All client work with factory through abstract
// * interface. They don't know concrete classes of factories.
// * Because of this, you can interchange concrete factories without
// * breaking clients.
// *
// * Clients don't know the concrete classes of created
// * products either, since abstract factory methods
// * returns abstract products.
// */
// 
// class Client
// {
// private:
// 	Factory *factory;
// 
// public:
// 	Client(Factory *f)
// 	{
// 		factory  = f;
// 	}
// 
// 	void draw()
// 	{
// 		Widget *w = factory->create_button();
// 		w->draw();
// 		display_window_one();
// 		display_windwo_two();
// 	}
// 
// 	void display_window_one()
// 	{
// 		Widget *w[] = {factory->create_button(), factory->create_menu()};
// 		w[0]->draw();
// 		w[1]->draw();
// 	}
// 
// 	void display_windwo_two()
// 	{
// 		Widget *w[] = {factory->create_button(), factory->create_menu()};
// 		w[0]->draw();
// 		w[1]->draw();
// 	}
// };
// 
// /**
// * Now the nasty switch statement is needed only once to 
// * pick and create a proper factory. Usually that's 
// * happening somewhere in program initialization code.
// */
// int main()
// {
// 	Factory *factory;
// #ifdef LINUX
// 	factory = new LinuxFactory;
// #else
// 	factory = new WindowsFactory;
// #endif
// 	Client *c = new Client(factory);
// 	c->draw();
// 	getchar();
// }





/*
Discussion. "Think of constructors as factories that churn out objects." Here we are allocating the
constructor responsibility to a factory object, and then using inheritance and virtual member functions
to provide a "virtual constructor" capability. So there are two dimensions of occurring. The client
uses the factory object instead of "new" to request instance; and the client "hard-wires" the family, or
class, of that factory only once, and throughout the remainder of the application only relies on the abstract
base class.
*/


#include <iostream>

using namespace std;

class Shape
{
public:
	Shape()
	{
		id_ = total_++;
	}
	virtual void draw() = 0;
protected:
	int id_;
	static int total_;
};

int Shape::total_ = 0;

class Circle : public Shape
{
public:
	void draw()
	{
		cout << "circle" << id_ << ": draw" << endl;
	}
};

class Square : public Shape
{
public:
	void draw()
	{
		cout << "square" << id_ << ": draw" << endl;
	}
};

class Ellipse : public Shape
{
public:
	void draw()
	{
		cout << "ellipse " << id_ << ": draw" << endl;
	}
};

class Rectangle : public Shape
{
public:
	void draw()
	{
		cout << "rectangle " << id_ << ": draw" << endl;
	}
};

class Factory
{
public:
	virtual Shape* createCurvedInstance() = 0;
	virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory
{
public:
	Shape* createCurvedInstance()
	{
		return new Circle;
	}
	Shape* creatStraightInstance()
	{
		return new Square();
	}
};

class RobustShapeFactory : public Factory
{
public:
	Shape* createCurvedInstance()
	{
		return new Ellipse;
	}
	Shape* createStraightInstance()
	{
		return new Rectangle;
	}
};

int main()
{
#ifdef SIMPLE
	Factory *facotry = new SimpleShapeFactory;
#else
	Factory *factory = new RobustShapeFactory;
#endif
	Shape* shapes[3];

	shapes[0] = factory->createCurvedInstance();
	shapes[1] = factory->createStraightInstance();
	shapes[2] = factory->createCurvedInstance();

	for (unsigned int i = 0; i < 3; ++i )
	{
		shapes[i]->draw();
	}

	getchar();
}