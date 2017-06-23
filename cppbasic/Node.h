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

class BinaryNode : public Node // û��ʵ�ֻ�����麯����������Ȼ�ǳ�����
{
public:
	BinaryNode(Node* left, Node* right) : left_(left), right_(right) {}
	virtual ~BinaryNode();
protected:
	Node* const left_;
	Node* const right_; // constλ��*�ұߣ�ָ�뱾���ܸı�
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

// �ٿ�41
#endif // NODE_H_