#include "Node.h"
#include <iostream>
#include <cmath>

double NumberNode::Calc(void) const
{
	return number_;
}

BinaryNode::~BinaryNode()
{
	if (left_)
		delete left_;
	if (right_)
		delete right_;
}

double AddNode::Calc(void) const
{
	return left_->Calc() + right_->Calc();
}

double SubNode::Calc(void) const
{
	return left_->Calc() - right_->Calc();
}

double MultiplyNode::Calc(void) const
{
	return left_->Calc() * right_->Calc();
}

double DivideNode::Calc(void) const
{
	double divisor = right_->Calc();
	if (divisor != 0) {
		return left_->Calc() / divisor;
	} else {
		std::cout << "Error:Divided by zero!" << std::endl; 
		return HUGE_VAL;
	}
}

UnaryNode::~UnaryNode()
{
	if (child_)
		delete child_;
}

double UMinusNode::Calc(void) const
{
	return - child_->Calc();
}