#pragma once
#include"shape.h"

class Rectangle :public Shape {
public:
	Rectangle(double length, double width) : m_length(length), m_width(width) {
		if (length <= 0 || width <= 0)
			throw ErrorInfo{ __FILE__, __LINE__ };
	}
	virtual ~Rectangle() {}

	virtual double perimeter() const
	{
		return 2 * (m_length + m_width);
	}

	virtual double area() const
	{
		return m_length * m_width;
	}

	virtual void shapeType() const
	{
		cout << "¾ØÐÎ ";
	}

private:
	double m_length, m_width;
};