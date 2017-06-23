#ifndef SHAPE_H_
#define SHAPE_H_

class Shape                  // ≥ÈœÛ¿‡
{
public:
	virtual void Draw() = 0;
	virtual ~Shape();
};

class Circle : public Shape
{
public:
	void Draw();
	~Circle();
};

class Square : public Shape
{
public:
	void Draw();
	~Square();
};

class Rectangle : public Shape
{
public:
	void Draw();
	~Rectangle();
};


#endif // SHAPE_H_