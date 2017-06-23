#ifndef NODE_H_
#define NODE_H_

class Node 
{
public:
	virtual double Calc(void) const = 0;
	virtual ~Node(void) {}
};

class NumberNode : public Node 
{
public:
	NumberNode(double number) : number_(number) {}
	double Calc(void) const;
private:
	double number_;
};

class BinaryNode : public Node // 没有实现基类的虚函数，该类仍然是抽象类
{
public:
	BinaryNode(Node* left, Node* right) : left_(left), right_(right) {}
	virtual ~BinaryNode();
protected:
	Node* const left_;
	Node* const right_; // const位于*右边，指针本身不能改变
};

class UnaryNode : public Node
{
public:
	UnaryNode(Node* child) : child_(child) {}
	virtual ~UnaryNode();
protected:
	Node* child_;
};

class AddNode : public BinaryNode
{
public:
	AddNode(Node* left, Node* right) : BinaryNode(left, right) {}
	double Calc(void) const;
};

class SubNode : public BinaryNode
{
public:
	SubNode(Node* left, Node* right) : BinaryNode(left, right) {}
	double Calc(void) const;
};

class MultiplyNode : public BinaryNode
{
public:
	MultiplyNode(Node* left, Node* right) : BinaryNode(left, right) {}
	double Calc(void) const;
};

class DivideNode : public BinaryNode
{
public:
	DivideNode(Node* left, Node* right) : BinaryNode(left, right) {}
	double Calc(void) const;
};

class UMinusNode : public UnaryNode	
{
public:
	UMinusNode(Node* child) : UnaryNode(child) {}
	double Calc(void) const;
};

// 再看41
#endif // NODE_H_