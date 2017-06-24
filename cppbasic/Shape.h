#ifndef SHAPE_H_
#define SHAPE_H_

class Shape                  // 鎶借薄绫�
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