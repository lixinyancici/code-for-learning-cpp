#include "Shape.h"
#include "DynBase.h"
#include <iostream>
using std::cout;
using std::endl;

Shape::~Shape() 
{
	cout << "~Shape ..." << endl;
}

void Circle::Draw()
{
	cout << "Circle::Draw() ..." << endl;
}

Circle::~Circle()
{
	cout << "~Circle ..." << endl;
}

void Square::Draw()
{
	cout << "Square::Draw() ..." << endl;
}

Square::~Square()
{
	cout << "~Square ..." << endl;
}

void Rectangle::Draw()
{
	cout << "Rectangle::Draw() ..." << endl;
}

Rectangle::~Rectangle()
{
	cout << "~Rectangle ..." << endl;
}

REGISTER_CLASS(Circle);
REGISTER_CLASS(Square);
REGISTER_CLASS(Rectangle);

/*class CircleRegister
{
public: 
	static void* NewInstance()
	{
		return new Rectangle;
	}
private:
	static Register reg_;
};
Register CircleRegister::reg_("Circle", CircleRegister::NewInstance);*/