#pragma once
#include"shape.h"

class Square :public Shape {
public:
	Square(double side) : m_side(side) {
		if (side <= 0)
			throw ErrorInfo{ __FILE__, __LINE__ };
	}
	virtual ~Square() {}

	virtual double perimeter() const
	{
		return 4 * m_side;
	}

	virtual double area() const
	{
		return m_side * m_side;
	}

	virtual void shapeType() const
	{
		cout << "Õý·½ÐÎ ";
	}

private:
	double m_side;
};